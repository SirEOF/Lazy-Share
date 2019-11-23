# This script decodes the files recieved

for i in ./*.txt ; do
    mv $i bb.txt 
    base64 -d bb.txt > $i
    rm -r bb.txt
done