if [ ! -f exec01 ]; then
    # run your scripts here
    echo "exec01"


    # create a flag file to check if we are resuming from reboot.
    touch exec01
    exit 0
fi

if [ ! -f exec02 ]; then
    # run your scripts here
    echo "exec02"
    
    # create a flag file to check if we are resuming from reboot.
    touch exec02
    exit 0
fi


if [ ! -f exec03 ]; then
    # run your scripts here
    echo "exec03"
    
    # create a flag file to check if we are resuming from reboot.
    touch exec03
fi


echo "Cleaning"
rm -f exec01
rm -f exec02
rm -f exec03

exit 0