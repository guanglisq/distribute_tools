g++ -o test rerosHandlers.c rerosMsgTypes.c  rerosParaConfig.h usrInit.c -I./ -I ../../distribute_tools/distribute_src/node/include/ -I ../../distribute_tools/distribute_src/master/include/ -I ../../distribute_tools/distribute_src/xmlrpc/include/ -L ../../distribute_tools/distribute_src/lib/ -lpthread -lmaster -lxmlrpc -lnode


g++ -o test usrInit.c -I ./code/ -I ./node/include/ -I ./master/include/ -I ./xmlrpc/include/ -L ./lib/ -lpthread -lmaster -lxmlrpc -lnode -luser


g++ -c rerosHandlers.c rerosMsgTypes.c rerosParaConfig.h -I ./ -I ../../distribute_tools/distribute_src/node/include/


ar crv libuser.a rerosHandlers.o rerosMsgTypes.o rerosParaConfig.h.gch
