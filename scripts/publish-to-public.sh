#!/usr/bin/env bash
pushd .
cp -r build/html/** public/

popd || exit