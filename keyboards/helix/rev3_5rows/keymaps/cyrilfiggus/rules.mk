DEFAULT_FOLDER = helix/rev3_5rows
HELIX_TOP_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
LTO_ENABLE = yes			# Lessens compile size

# AVR MCU options
MCU = atmega32u4
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes

# If using Sparkfun RP2040 Pro Micro
# CONVERT_TO = promicro_rp2040

# Useful Features
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
EXTRAKEY_ENABLE = yes		# Audio control and System control
GRAVE_ESC_ENABLE = yes 		# Esc when pressed, Grv when Shift or GUI held
MAGIC_ENABLE = yes			# Swap keys AFTER keyboard initialized
MOUSEKEY_ENABLE = yes
ONESHOT_ENABLE = yes
VIA_ENABLE = no 			# Enables real-time keymap changes

# Lighting
BACKLIGHT_ENABLE = no   	# Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no     	# Enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
RGB_MATRIX_CUSTOM_USER = yes  # Custom effect that sets colour based on key type
SLEEP_LED_ENABLE = no 		# Breathing sleep LED during USB suspend

# OLED
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
SRC += oled_display.c

# Encoder
ENCODER_MAP_ENABLE = yes 	# Enables rotary encoder keymap

# Unavailable features
AUDIO_ENABLE = no 			# Enable the audio subsystem.
BLUETOOTH_ENABLE = no
DIP_SWITCH_ENABLE = no
PS2_ENABLE = no

# Unused features to save compile space
BOOTMAGIC_ENABLE = no
COMBO_ENABLE = no 			# Key combo feature
COMMAND_ENABLE = no    		# Commands for debug and configuration
CONSOLE_ENABLE = no			# Console for debug
LEADER_ENABLE = no 			# Enable leader key chording
MIDI_ENABLE = no
NKRO_ENABLE = no			# USB N-Key Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
SECURE_ENABLE = no
SPACE_CADET_ENABLE = no 	# Tap LShift for (, RShift for ), Shift when held
STENO_ENABLE = no
TAP_DANCE_ENABLE = no
UNICODE_ENABLE = no
