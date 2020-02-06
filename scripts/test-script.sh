#!/usr/bin/env bash
pushd .
imgfile=screenshot.png

imlib2_grab "${imgfile}"
# import -window root -density 3840x2160 -depth 8 -quality 40 ${imgfile}

# shellcheck disable=SC2034 # Unused variable _i left for readability
imblur -i "${imgfile}" -o "${imgfile}" -r 3 -c 5 -q yes -l 69
feh ${imgfile}

popd || exit