#!/usr/bin/env bash
pushd .
mkdir -p public/
cp -r build/html/** public/

popd || exit