#!/bin/sh

#
# # -*- coding: utf-8, tab-width: 3 -*-

#                                                           ___                                            #
#                                                          / _ \                                           #
#                                            _   _  _   _ | | | |                                          #
#                                           | | | || | | || | | |                                          #
#                                           | |_| || |_| || |_| |                                          #
#                                           | ._,_| \___/  \___/                                           #
#                                           | |                                                            #
#                                           |_|                                                            #

# repo_clean.sh
#
# Copyright (C) 2023 mu578. All rights reserved.
#

cmd_pushd () {
	command pushd "$@" > /dev/null
}

cmd_popd () {
	command popd "$@"  > /dev/null
}

REPO_PATH=$(realpath `dirname ${0}`)

find ${REPO_PATH} -type f -iname .DS_store -print0 | xargs -0 rm -f

find ${REPO_PATH} -iname "*.sh"   | xargs chmod 644
find ${REPO_PATH} -iname "*.mk"   | xargs chmod 644
find ${REPO_PATH} -iname "*.md"   | xargs chmod 644
find ${REPO_PATH} -iname "*.yml"  | xargs chmod 644
find ${REPO_PATH} -iname "*.json" | xargs chmod 644
find ${REPO_PATH} -iname "*.c"    | xargs chmod 644
find ${REPO_PATH} -iname "*.h"    | xargs chmod 644
find ${REPO_PATH} -iname "*.hpp"  | xargs chmod 644
find ${REPO_PATH} -iname "*.cpp"  | xargs chmod 644
find ${REPO_PATH} -iname "*.cc"   | xargs chmod 644

chmod 644 ${REPO_PATH}/.editorconfig  2> /dev/null
chmod 644 ${REPO_PATH}/.gitignore     2> /dev/null
chmod 644 ${REPO_PATH}/.gitattributes 2> /dev/null

cmd_pushd ${REPO_PATH}
# git clean -f -d 2> /dev/null
cmd_popd

# EOF