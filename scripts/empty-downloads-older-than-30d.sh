victim=~/Downloads
echo Calculating $victim size...
echo $victim trash size: `du -sh $victim | cut -f1`
echo -n "Emptying $victim items older than 30 days, please be patient..."
find $victim -mtime +30d -exec rm -fr {} \; &> /dev/null
echo Done
echo Current $victim size: `du -sh $victim | cut -f1`
