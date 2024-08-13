# Arduino Build Server
Arduino Build Server - build arduino and not only arduino projects on remote host and upload on current. 

For example you can connect rpi and arduino via usb cable and upload sketches to arduino from rpi. But rpi compiles sketches slow, so you can boost it, if compile sketch on fast machine and than upload from rpi. 

Why you can't compile arduino sketch on pc and upload it from pc? - You can, but when it is not bundled solution, when you can easily disconnect arduino from rpi and connect to pc.

# Protocol

Direct source code sending pipeline (only one file for now, implement tar.gz archiving in future)

```
PC -> code_pkt

code_pkt: header_0 -> header_1 -> source code
header_0: board name char buff (example: arduino:avr:mega:cpu=atmega2560)
header_1: project name char buff (example: AAAA) if == onetime, generate name via current server timestamp
```

Git server pulling (no command verification in Makefile, so it can be dangerous, while giving access to other users)

```
PC -> git_req_pkt

git_req_pkt: git_link|MakefileTargetName
example: https://github.com/ret7020/aa.git|all
```