base_dir=~/src/tools/qmk_firmware
set -ex
cp keymap.c $base_dir/keyboards/crkbd/keymaps/markstos/keymap.c
cp config.h $base_dir/keyboards/crkbd/keymaps/markstos/config.h
cp readme.md $base_dir/keyboards/crkbd/keymaps/markstos/readme.md
cp rules.mk $base_dir/keyboards/crkbd/keymaps/markstos/rules.mk

