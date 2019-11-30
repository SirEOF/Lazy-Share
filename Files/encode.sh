# This script converts the files to base64

for i in ./*.txt ; do
    mv $i bb.txt 
    base64 bb.txt > $i
    rm -r bb.txt
done
