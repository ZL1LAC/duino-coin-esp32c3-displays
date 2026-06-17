#!/usr/bin/env bash
# Install TFT_eSPI board setup + ESP32-C3 SPI patch for CI/local builds.
# Usage: setup-tft-espi.sh <esp32c3-minitv|esp32c3-round128> [TFT_eSPI_dir]
set -euo pipefail

BOARD="${1:?board profile required}"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TFT_DIR="${2:-${ARDUINO_LIBRARIES:-$HOME/Arduino/libraries}/TFT_eSPI}"

if [[ ! -d "$TFT_DIR" ]]; then
  echo "TFT_eSPI not found at: $TFT_DIR" >&2
  exit 1
fi

mkdir -p "$TFT_DIR/User_Setups"

case "$BOARD" in
  esp32c3-minitv)
    SRC="$ROOT/boards/esp32c3-minitv/ST7735_setup.h"
    cp "$SRC" "$TFT_DIR/User_Setup.h"
    cp "$SRC" "$TFT_DIR/User_Setups/Setup_Spotpear_ESP32C3_144.h"
    grep -q '^#define USER_SETUP_ID' "$TFT_DIR/User_Setup.h" || \
      sed -i '1i#define USER_SETUP_ID 300' "$TFT_DIR/User_Setup.h"
    ;;
  esp32c3-round128)
    SRC="$ROOT/patches/TFT_eSPI/Setup_ESP32_2424S012.h"
    cp "$SRC" "$TFT_DIR/User_Setup.h"
    cp "$SRC" "$TFT_DIR/User_Setups/Setup_ESP32_2424S012.h"
    ;;
  *)
    echo "unknown board: $BOARD" >&2
    exit 1
    ;;
esac

# Default User_Setup_Select.h already includes <User_Setup.h> — do not replace it
# (the stock file also loads ST7735_Defines.h / GC9A01_Defines.h after the setup).

C3_H="$TFT_DIR/Processors/TFT_eSPI_ESP32_C3.h"
if [[ -f "$C3_H" ]] && ! grep -q 'DR_REG_SPI2_BASE' "$C3_H"; then
  cat >> "$C3_H" <<'EOF'

// duino-coin-boards: ESP32-C3 SPI fix (Arduino ESP32 core 3.x)
#if CONFIG_IDF_TARGET_ESP32C3
  #ifdef REG_SPI_BASE
    #undef REG_SPI_BASE
  #endif
  #define REG_SPI_BASE(i) DR_REG_SPI2_BASE
#endif
EOF
fi

echo "TFT_eSPI configured for $BOARD at $TFT_DIR (User_Setup.h)"
