
keyvalue=(
    "mkdir                     ->  /etc/"
    "/src/conf/WebServer.conf  ->  /etc/viks.config"
    "mkdir                     ->  /usr/"
    "mkdir                     ->  /usr/share/"
    "mkdir                     ->  /usr/share/licenses/"
    "mkdir                     ->  /usr/share/licenses/viks/"
    "/LICENSE                  ->  /usr/share/licenses/viks/LICENSE"
    "mkdir                     ->  /opt/"
    "mkdir                     ->  /opt/viks/"
    "/src/Webserver            ->  /opt/viks/WebServer"
)

# frombase 指定文件的當前根目錄，要求通過$frombase$key可以指向需求文件
frombase="."
# tobase 指定遷移目的地，要求通過$tobase$key可以指向目標地址
tobase="./dir"
# 指向部署的根目錄，爲空時，則爲系統的根目錄。
realbase=""

# 本腳本爲鏈式調用，除了腳本自身調用的arraysetup方法，用戶請自己追加需要的方法
#
# ./deb-packup.sh log 输出log
# ./deb-packup.sh collect 根據$keyvalue，收集文件到$tobase目錄下，用於打包
# ./deb-packup.sh discollect 根據$keyvalue的目標地址，逐個刪除。

log=0
log(){
    log=1
}

arraysetup(){
    tmppath="/tmp/viks/"
    fromlistdir=$tmppath"fromlist"
    tolistdir=$tmppath"tolist"
    if [ ! -d $tmppath ]; then 
        mkdir $tmppath 
    fi

    touch $fromlistdir && cat /dev/null>$fromlistdir
    touch $tolistdir && cat /dev/null>$tolistdir
    for i in ${!keyvalue[@]};do
        echo ${keyvalue[$i]} | tr -d ' ' | sed 's/->/ /' | awk '{print $1}' >>$fromlistdir
        echo ${keyvalue[$i]} | tr -d ' ' | sed 's/->/ /' | awk '{print $2}' >>$tolistdir
    done
    fromlist=($(awk '{print $1}' $fromlistdir)) 
    tolist=($(awk '{print $1}' $tolistdir)) 
    echo "=== arraysetup() done ==="
}


collect(){
    for i in ${!fromlist[@]};do
        if [ "${fromlist[$i]}" = "mkdir" ];then 
            if [ "$log" = "1" ];then 
                echo "mkdir $tobase${tolist[$i]}" 
            fi
            if [ ! -d $tobase${tolist[$i]} ];then
                if [ "$log" = "1" ];then 
                    echo "dir not found; create $tobase${tolist[$i]}"
                fi
                mkdir $tobase${tolist[$i]} 
            fi
        else
            if [ "$log" = "1" ];then 
                echo "copy $frombase${fromlist[$i]} to $tobase${tolist[$i]}"
            fi
            cp $frombase${fromlist[$i]} $tobase${tolist[$i]}
        fi
    done
    echo "=== copy done, collect() done ==="
}

discollect(){
    for i in ${!tolist[@]};do
        if [ "${fromlist[$i]}" = "mkdir" ];then 
            if [ "$log" = "1" ];then 
                echo "$tobase${tolist[$i]} is a dir"
            fi
            if [ -d $tobase${tolist[$i]} ];then
                if [ "$log" = "1" ];then 
                    echo "delete dir $tobase${tolist[$i]}"
                fi
                rm -r $tobase${tolist[$i]} 
            fi
        else
            if [ "$log" = "1" ];then 
                echo "rm $tobase${tolist[$i]}"
            fi
            rm $tobase${tolist[$i]}
        fi
    done
    echo "=== delete copy done, discollect() done ==="
}

deploy(){
    for i in ${!fromlist[@]};do
        if [ "${fromlist[$i]}" = "mkdir" ];then 
             if [ "$log" = "1" ];then 
                echo "mkdir $realbase${tolist[$i]}"
            fi
            if [ ! -d $realbase${tolist[$i]} ];then
                if [ "$log" = "1" ];then 
                    echo "dir not found; create $realbase${tolist[$i]}"
                fi
                mkdir $realbase${tolist[$i]} 
            fi
        else
            if [ "$log" = "1" ];then 
                echo "copy $frombase${fromlist[$i]} to $realbase${tolist[$i]}"
            fi
            cp $frombase${fromlist[$i]} $realbase${tolist[$i]}
        fi
    done
    echo "=== copy done, deploy() done ==="
}

disdeploy(){
    for i in ${!tolist[@]};do
        if [ "${fromlist[$i]}" = "mkdir" ];then 
            if [ "$log" = "1" ];then 
                echo "$realbase${tolist[$i]} is a dir"
            fi
        else
            if [ "$log" = "1" ];then 
               echo "rm $realbase${tolist[$i]}"
            fi 
            rm $realbase${tolist[$i]}
        fi
    done
    echo "=== delete copy done, disdeploy() done ==="
}

packup_deb(){
    return 0;
}
packup_arch(){
    return 0;
}


clear(){
    if [ -f $fromlistdir ]; then 
        rm $fromlistdir 
        echo "clear $fromlistdir"
    fi
    if [ -f $tolistdir ]; then 
        rm $tolistdir 
        echo "clear $tolistdir"
    fi
    echo "clear done"
}



arraysetup
for arg in "$@"
do
    $arg
done
