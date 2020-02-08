#!/usr/bin/env bash
pushd .
mkdir -p public/
cp -r build/xml/** doc/
cp build/deps.png doc/
popd || exit
