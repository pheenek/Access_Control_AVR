# Access_Control_AVR
A biometric access control system, powered by the AVR ATMega328P microcontroller

### Construction

![Access Control System Schematic](https://pheenek.com/me/wp-content/uploads/2023/10/Screenshot_20231001_193738-1024x693.png)
#### Hardware
- Custom PCB including:
    - ATMega328P microcontroller
    - Buzzer and its switching circuit
    - Connectors for: the OLED display, solenoid lock, fingerprint reader module, magnetic contact switch, push button
- OLED display module, 1.3 inch 128x64 resolution
- Solenoid lock
- Fingerprint reader module
- Magnetic contact switch
- Push button
- 5V power supply adapter


#### Software
The software for the system is mainly architected around a state machine. The system's operation is divided
into a number of finite states. The states include:
- **Default state** - This is the default state of the system. When in this state, the system waits to read fingerprints on the fingerprint reader, performs verification, and grants, or denies access.
- **Pin state** - The system enters this state from the default state when the user requests to access the configuration menu (administrator menu). When in this state, the system reads passcode input by the user on the keypad to and grants or denies access to the user depending on the security code entered. The system doesn’t perform any fingerprint verification in this state.
- **Navigation state** -  In this state, the keypad would primarily be used to navigate the configuration menu. Fingerprint verification is also not performed while in this state.
- **Idle state** - This state (keypad state) is used when enrolling fingerprints to the system, at the stage when the only input required is the new fingerprint to be enrolled. Keypad access is paused in this state, with the exception of one particular key which enables navigating to the previous menu.

### Shortcomings
- The system doesn't include a power back-up
- Ability to register the same fingerprint multiple times

### Possible future Improvements
- Include a back-up power source
- System remains in sleep mode when running on power back-up and not actively perfroming any operations
- Implementation of a more robust user database to manage fingerprint data
