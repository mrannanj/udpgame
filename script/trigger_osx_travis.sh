#!/bin/bash

die () {
    echo "error: $@" >&2
    exit 1
}

[ -z "$(git status --porcelain)" ] || die "repository not clean"

ROOT=$(git root)
CUR_BRANCH=$(git rev-parse --abbrev-ref HEAD)
OSX_BRANCH=${CUR_BRANCH}-osx

cd ${ROOT}
git checkout -B "${OSX_BRANCH}"
sed -e "s/language: cpp/language: objective-c/" -i .travis.yml
sed -e "/clang++/d" -i .travis.yml

git add .
git commit -m "trigger travis for osx"

#FIXME: optional origin
git push -f origin "${OSX_BRANCH}"
git checkout "${CUR_BRANCH}"
