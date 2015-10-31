# lxqt-openssh-askpass

This is a very small helper app for ssh-agent.

Example setup:

- Run the lxqt-config-session.
- Add new item into the "Environment (Advanced)": `SSH_ASKPASS=lxqt-openssh-askpass`
- If you want to register your keys on session startup add new item to "Autostart" tab. For example:
 - name: ssh-add
 - command: ssh-add
 - wait for system tray: false
- logout/login/enjoy
