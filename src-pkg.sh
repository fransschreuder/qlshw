DISTS="trusty xenial yakkety"
#cp debian-src/* debian
RELEASE=1.2
git clone . ../qlshw-$RELEASE
cd ..
cd qlshw-$RELEASE
rm -rf .git
cd ..
tar -zcvf qlshw_$RELEASE.orig.tar.gz qlshw-$RELEASE
cd qlshw-$RELEASE
COUNT=0
for DIST in ${DISTS} ; do
	COUNT=$(($COUNT-1))
	
	dch -D $DIST -m -v $RELEASE$COUNT -b
	
	debuild -S -k8AD5905E
	
	
done
