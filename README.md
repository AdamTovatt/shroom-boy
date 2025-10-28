# Shroom Boy
This repository contains code for the Shroom Boy software.

### Useful Commands
To set the target to esp32 c3:
```
idf.py set-target esp32c3
```

To build the project:
```
idf.py build
```

To flash the project to the device:
```
idf.py -p (YOUR PORT) flash
```

> [!TIP]
> On Windows, the command "mode" can be used to list available COM ports. It's probably not COM1 so if there is just one other port, it's likely that one.