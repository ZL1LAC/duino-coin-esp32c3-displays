#!/usr/bin/env bash
# Build merged flash images for boards listed in boards/registry.json.
# Usage: build-firmware.sh [board-id|all]
set -euo pipefail

TARGET="${1:-all}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SKETCH="$ROOT/ESP_Code"
DIST="$ROOT/firmware/dist"
REGISTRY="$ROOT/boards/registry.json"

if [[ "$TARGET" == "all" ]]; then
  mapfile -t BOARDS < <(python3 "$ROOT/scripts/registry.py" list)
else
  BOARDS=("$TARGET")
fi

command -v arduino-cli >/dev/null || {
  echo "arduino-cli not found. Install: https://arduino.github.io/arduino-cli/" >&2
  exit 1
}

if [[ "${SKIP_DEPS:-0}" != "1" ]]; then
  arduino-cli core update-index
  arduino-cli core install esp32:esp32
  arduino-cli lib install "ArduinoJson" "WiFiManager" "TFT_eSPI" "U8g2"
fi

LIB_DIR="${ARDUINO_LIBRARIES:-$HOME/Arduino/libraries}"
TFT_DIR="$LIB_DIR/TFT_eSPI"

if [[ ! -d "$TFT_DIR" ]]; then
  echo "TFT_eSPI not found at $TFT_DIR" >&2
  exit 1
fi

GIT_SHA="$(git -C "$ROOT" rev-parse --short HEAD 2>/dev/null || echo unknown)"
GIT_TAG="$(git -C "$ROOT" describe --tags --always 2>/dev/null || echo dev)"

board_field() {
  python3 - "$1" "$2" "$REGISTRY" <<'PY'
import json, sys
field, board_id, path = sys.argv[1:4]
entry = next(b for b in json.load(open(path))["boards"] if b["id"] == board_id)
fw = entry["firmware"]
if field == "name":
    print(entry["name"])
elif field == "fqbn":
    print(fw["fqbn"])
elif field == "chip":
    print(fw.get("esptool_chip", "esp32c3"))
PY
}

build_board() {
  local board="$1"
  local out="$DIST/$board"
  local fqbn name chip
  fqbn="$(board_field fqbn "$board")"
  name="$(board_field name "$board")"
  chip="$(board_field chip "$board")"

  mkdir -p "$out"

  echo "=== Building $board ($name) ==="
  bash "$ROOT/scripts/prepare-settings.sh" "$board"
  bash "$ROOT/scripts/setup-tft-espi.sh" "$board" "$TFT_DIR"

  arduino-cli compile \
    --fqbn "$fqbn" \
    --output-dir "$out" \
    --export-binaries \
    "$SKETCH"

  local app bootloader partitions boot_app0 merged
  app="$(find "$out" -name '*.ino.bin' ! -name '*.bootloader.bin' ! -name '*.partitions.bin' | head -n1)"
  bootloader="$(find "$out" -name '*.bootloader.bin' | head -n1)"
  partitions="$(find "$out" -name '*.partitions.bin' | head -n1)"
  boot_app0="$(find "$out" -name 'boot_app0.bin' | head -n1)"

  if [[ -z "$app" || -z "$bootloader" || -z "$partitions" ]]; then
    echo "Build artifacts missing under $out" >&2
    find "$out" -type f >&2 || true
    exit 1
  fi

  merged="$out/${board}-merged-flash.bin"
  merge_args=(--chip "$chip" merge_bin -o "$merged" --flash_mode dio --flash_freq 80m --flash_size 4MB)
  merge_args+=(0x0 "$bootloader")
  merge_args+=(0x8000 "$partitions")
  if [[ -n "$boot_app0" && -f "$boot_app0" ]]; then
    merge_args+=(0xe000 "$boot_app0")
  fi
  merge_args+=(0x10000 "$app")

  python3 -m esptool "${merge_args[@]}"

  python3 - "$board" "$name" "$GIT_SHA" "$GIT_TAG" "$merged" "$fqbn" "$chip" > "$out/manifest.json" <<'PY'
import json, sys
board, name, sha, tag, merged, fqbn, chip = sys.argv[1:8]
bin_name = merged.replace("\\", "/").split("/")[-1]
print(json.dumps({
    "board": board,
    "name": name,
    "software_version": "4.3",
    "git_sha": sha,
    "git_ref": tag,
    "fqbn": fqbn,
    "captive_portal": True,
    "first_run": "Connect to WiFi AP Duino-Coin and enter WiFi + Duino-Coin credentials.",
    "flash": {
        "merged_bin": bin_name,
        "esptool_chip": chip,
        "esptool_command": (
            f"python -m esptool --chip {chip} --port COM_PORT write_flash 0x0 {bin_name}"
        ),
    },
}, indent=2))
PY

  cat > "$out/FLASH.txt" <<EOF
Board: $name
Profile: $board
Git: $GIT_SHA ($GIT_TAG)

Flash the merged binary (full chip image):
  python -m esptool --chip $chip --port COM_PORT write_flash 0x0 ${board}-merged-flash.bin

Windows: replace COM_PORT with your port (e.g. COM14).
Upload speed 115200 if the link is unreliable.

First boot: join WiFi network "Duino-Coin" and enter your home WiFi + Duino-Coin username/key.
EOF

  echo "Built: $merged"
}

rm -rf "$DIST"
mkdir -p "$DIST"

for board in "${BOARDS[@]}"; do
  build_board "$board"
done

echo "Done. Output: $DIST"
