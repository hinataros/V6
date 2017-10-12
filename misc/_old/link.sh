#!/bin/bash

sl="/usr/local/etc/rls_sl"

if [ $# = 0 ]; then
    sudo rm -rf ${sl}
    sudo mkdir -p ${sl}

    src_dir=$(cd $(dirname $0)/..; pwd)

    sudo ln -s "${src_dir}/data" "${sl}/data"

    cd "${src_dir}/yaml"
    yaml_dir="${src_dir}/yaml"
    declare -a config=(`find config -name \*.yaml`)
    declare -a model=(`find model -name \*.yaml`)

    sudo mkdir -p "${sl}/config"
    sudo mkdir -p "${sl}/model"

    i=0
    while [ ${config[i]} ]
    do
	sudo ln -s "${yaml_dir}/${config[i]}" "${sl}/${config[i]}"
	((i++))
    done

    i=0
    while [ ${model[i]} ]
    do
	sudo ln -s "${yaml_dir}/${model[i]}" "${sl}/${model[i]}"
	((i++))
    done

    declare -a controller=(`find work -type d`)
    i=1
    while [ ${controller[i]} ]
    do
	sudo mkdir -p "${sl}/${controller[i]}"
    	((i++))
    done

    declare -a work=(`find work -name \*.yaml`)

    i=0
    while [ ${work[i]} ]
    do
    	sudo ln -s "${yaml_dir}/${work[i]}" "${sl}/${work[i]}"
    	((i++))
    done

    echo "linked..."

elif [ $# = 1 ]; then
    if [ $1 = "clean" ]; then
	sudo rm -rf ${sl}
	echo "unlinked..."
    else
	echo "arguments is incorrect..."
    fi
fi
