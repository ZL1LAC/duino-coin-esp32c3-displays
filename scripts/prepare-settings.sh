#!/usr/bin/env bash
# Generate ESP_Code/Settings.h for a firmware release build.
# Usage: prepare-settings.sh <esp32c3-minitv|esp32c3-round128>
set -euo pipefail

BOARD="${1:?board profile required}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/ESP_Code/Settings.h"
EXAMPLE="$ROOT/ESP_Code/Settings.h.example"

cp "$EXAMPLE" "$OUT"

python3 - "$BOARD" "$OUT" <<'PY'
import re
import sys

board, path = sys.argv[1], sys.argv[2]
text = open(path, encoding="utf-8", errors="replace").read()

def set_define(name, enabled):
    global text
    if enabled:
        text = re.sub(rf"^//\s*#define {name}\s*$", f"#define {name}", text, flags=re.M)
        text = re.sub(rf"^//\s*#define {name}\b", f"#define {name}", text, flags=re.M)
    else:
        text = re.sub(rf"^#define {name}\s*$", f"// #define {name}", text, flags=re.M)

# Release builds use WiFiManager so users configure after flash.
set_define("CAPTIVE_PORTAL", True)

if board == "esp32c3-minitv":
    set_define("DISPLAY_ST7735", True)
    set_define("DISPLAY_GC9A01", False)
elif board == "esp32c3-round128":
    set_define("DISPLAY_ST7735", False)
    set_define("DISPLAY_GC9A01", True)
else:
    raise SystemExit(f"unknown board profile: {board}")

open(path, "w", encoding="utf-8").write(text)
PY

echo "Wrote $OUT for profile: $BOARD (CAPTIVE_PORTAL enabled)"
