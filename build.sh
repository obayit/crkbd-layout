# if this command is run from inside the keymap directory:
base_dir=~/src/tools/qmk_firmware
set -ex

cd $base_dir/keyboards/crkbd/keymaps/markstos
qmk compile -e CONVERT_TO=rp2040_ce

# if not run from the directory of the keymap, then add the -km option

