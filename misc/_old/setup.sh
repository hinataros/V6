#!/bin/bash

src_dir=$(cd $(dirname $0)/..; pwd)

echo $0

if [ $# = 1 -o $# = 2 ]; then
    if [ $1 = "clean" ]; then
	if [ $# = 2 ]; then
	    echo -n "delete $2 directory? [y/] "
	    read temp
	    if [ ${temp} = "y" ]; then
		declare -a dir=(`find -name $2`)
		i=0
		while [ ${dir[i]} ]
		do
		    rm -r "${src_dir}/${dir[i]}"
		    echo "${src_dir}/${dir[i]} deleted..."
		    ((i++))
		done
	    else
		echo "exit..."
		exit 0
	    fi
	else
	    echo -n "delete data directory? [y/] "
	    read temp
	    if [ ${temp} = "y" ]; then
    		rm -rf data
    		echo "${src_dir}/data deleted..."
	    else
		echo "exit..."
		exit 0
	    fi
	fi
    elif [ $1 = "make" -o $1 = "remake" -o $1 = "re0make" ]; then
	if [ $# = 2 ]; then
	    if [ $1 = "re0make" ]; then
		echo -n "delete data directory? [y/] "
		read temp
		if [ ${temp} = "y" ]; then
    		    rm -rf data
    		    echo "${src_dir}/data deleted..."
		else
		    echo "exit..."
		    exit 0
		fi
	    elif [ $1 = "remake" ]; then
		echo -n "delete $2 directory? [y/] "
		read temp
		if [ ${temp} = "y" ]; then
		    declare -a dir=(`find -name $2`)
		    i=0
		    while [ ${dir[i]} ]
		    do
			rm -r "${src_dir}/${dir[i]}"
			echo "${src_dir}/${dir[i]} deleted..."
			((i++))
		    done
		else
		    echo "exit..."
		    exit 0
		fi
	    fi

	    cd "${src_dir}/yaml"
	    declare -a controller=(`find work -type d`)

	    cd "${src_dir}/yaml/model"
	    yaml_dir="${src_dir}/yaml"

	    i=1
	    while [ ${controller[i]} ]
	    do
	    	controller=${controller[i]}
	    	controller="${controller##*/}"

	    	j=0
	    	declare -a model=(`find -name \*.yaml`)
	    	while [ ${model[j]} ]
	    	do

	    	    model=${model[j]}
	    	    model="${model%.*}"
	    	    model="${model##*/}"

	    	    mkdir -p "${src_dir}/data/dat/$2/${controller}:${model}"
	    	    mkdir -p "${src_dir}/data/dat/$2/${controller}:${model}/model"
	    	    mkdir -p "${src_dir}/data/dat/$2/${controller}:${model}/controller"
	    	    mkdir -p "${src_dir}/data/dat/$2/${controller}:${model}/gif"

	    	    mkdir -p "${src_dir}/data/eps/$2/${controller}:${model}/model"
	    	    mkdir -p "${src_dir}/data/eps/$2/${controller}:${model}/controller"

	    	    mkdir -p "${src_dir}/data/gif/$2/${controller}:${model}"

	    	    mkdir -p "${src_dir}/data/gp/$2/${controller}:${model}/library"
	    	    mkdir -p "${src_dir}/data/gp/$2/${controller}:${model}/model"
	    	    mkdir -p "${src_dir}/data/gp/$2/${controller}:${model}/controller"

	    	    mkdir -p "${src_dir}/data/movie/$2/${controller}:${model}"

	    	    mkdir -p "${src_dir}/data/pdf/$2/${controller}:${model}"

	    	    ((j++))
	    	done
	    	((i++))
	    done

	    echo "$2 created..."
	else
	    echo "作らねーのかい！！！"
	fi
    else
	echo "arguments is incorrect..."
    fi
else
    echo "Please arguments..."
fi

