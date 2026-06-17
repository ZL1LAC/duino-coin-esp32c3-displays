#!/usr/bin/env bash
# Build merged flash images for supported boards.
# Usage: build-firmware.sh [esp32c3-minitv|esp32c3-round128|all]
set -euo pipefail

TARGET="${1:-all}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
SKETCH="$ROOT/ESP_Code"
DIST="$ROOT/firmware/dist"
FQBN="esp32:esp32:esp32c3:UploadSpeed=115200,CDCOnBoot=cdc,PartitionScheme=huge_app"
BOARDS=()

if [[ "$TARGET" == "all" ]]; then
  BOARDS=(esp32c3-minitv esp32c3-round128)
else
  BOARDS=("$TARGET")
fi

command -v arduino-cli >/dev/null || {
  echo "arduino-cli not found. Install: https://arduino.github.io/arduino-cli/" >&2
  exit 1
}

arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli lib install "ArduinoJson" "WiFiManager" "TFT_eSPI"

TFT_DIR="$(arduino-cli lib list --format json | python3 -c "
import json, sys
for lib in json.load(sys.stdin):
    if lib.get('name') == 'TFT_eSPI':
        print(lib['install']['location'])
        break
")"

if [[ -z "$TFT_DIR" || ! -d "$TFT_DIR" ]]; then
  TFT_DIR="${ARDUINO_LIBRARIES:-$HOME/Arduino/libraries}/TFT_eSPI"
fi

GIT_SHA="$(git -C "$ROOT" rev-parse --short HEAD 2>/dev/null || echo unknown)"
GIT_TAG="$(git -C "$ROOT" describe --tags --always 2>/dev/null || echo dev)"

build_board() {
  local board="$1"
  local out="$DIST/$board"
  mkdir -p "$out"

  echo "=== Building $board ==="
  bash "$ROOT/scripts/prepare-settings.sh" "$board"
  bash "$ROOT/scripts/setup-tft-espi.sh" "$board" "$TFT_DIR"

  arduino-cli compile \
    --fqbn "$FQBN" \
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
  merge_args=(--chip esp32c3 merge_bin -o "$merged" --flash_mode dio --flash_freq 80m --flash_size 4MB)
  merge_args+=(0x0 "$bootloader")
  merge_args+=(0x8000 "$partitions")
  if [[ -n "$boot_app0" && -f "$boot_app0" ]]; then
    merge_args+=(0xe000 "$boot_app0")
  fi
  merge_args+=(0x10000 "$app")

  python3 -m esptool "${merge_args[@]}"

  local name
  case "$board" in
    esp32c3-minitv) name='Spotpear ESP32-C3 1.44" Mini TV (ST7735)' ;;
    esp32c3-round128) name='ESP32-2424S012 round (GC9A01 + touch)' ;;
    *) name="$board" ;;
  esac

  python3 - "$board" "$name" "$GIT_SHA" "$GIT_TAG" "$merged" "$FQBN" > "$out/manifest.json" <<'PY'
import json, sys
board, name, sha, tag, merged, fqbn = sys.argv[1:7]
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
        "merged_bin": merged.split("/")[-1],
        "esptool_chip": "esp32c3",
        "esptool_command": (
            f"python -m esptool --chip esp32c3 --port COM_PORT write_flash 0x0 {merged.split('/')[-1]}"
        ),
    },
}, indent=2))
PY

  cat > "$out/FLASH.txt" <<EOF
Board: $name
Profile: $board
Git: $GIT_SHA ($GIT_TAG)

Flash the merged binary (full chip image):
  python -m esptool --chip esp32c3 --port COM_PORT write_flash 0x0 ${board}-merged-flash.bin

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
