for i in `find -name *.c`; do indent  -sob  <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done
for i in `find -name *.cpp`; do indent  -sob  <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done
for i in `find -name *.h`; do indent  -sob <$i >/tmp/indent.tmp; cp /tmp/indent.tmp $i; done


