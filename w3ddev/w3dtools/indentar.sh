for i in `find -name *.c`; do indent -kr -sob -nut <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done
for i in `find -name *.cpp`; do indent -kr -nut <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done
for i in `find -name *.h`; do indent -kr -nut <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done


