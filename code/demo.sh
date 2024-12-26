
screen /dev/ttyUSB0 115200
# run ATD wait for connection
# press record then wait a bit
stty -F /dev/ttyUSB0 crtscts 115200
cat lipsum.txt > /dev/ttyUSB0


screen /dev/ttyUSB0 115200
# run ATA then press play wait for connection
stty -F /dev/ttyUSB0 crtscts 115200
cat /dev/ttyUSB0 | tee lipsum_cmp.txt
truncate -s $(stat -c %s lipsum.txt) lipsum_cmp.txt
diff --color lipsum.txt lipsum_cmp.txt

./send.sh /dev/ttyUSB0 lipsum.txt


./receive.sh /dev/ttyUSB0 lipsum_cmp.txt
truncate -s $(stat -c %s lipsum.txt) lipsum_cmp.txt
diff --color lipsum.txt lipsum_cmp.txt
