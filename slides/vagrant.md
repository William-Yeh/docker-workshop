name: inverse
layout: true
class: center, middle, inverse

---

# Lab #0: Vagrant 快速上手

---

layout: false
class: center, middle

`% cd docker-workshop/vagrant-tutorial`

---

class: center, middle

VM - Almost isolated environment inside the Host Machine

.percent90[![topology](img/lab-topology-1.svg)
]

---

# OS to be emulated

Take a look at `Vagrantfile` (simplified):

```yaml
Vagrant.configure(2) do |config|

  config.vm.box = "ubuntu/trusty64"

end
```

Vagrant *box* used here:

  - [`ubuntu/trusty64`](https://vagrantcloud.com/ubuntu/boxes/trusty64): Ubuntu 14.04 LTS (Trusty Tahr) 64-bit


.footnote[Explore [Atlas](https://atlas.hashicorp.com/boxes/search) site for more boxes.]

---

class: center, middle

# Open **VirtualBox** side by side<br/>to see effect...

---

# VM status

Show current status of all VMs:

```bash
% vagrant status
```

---

# Login

Power on the default VM:

```bash
% vagrant up
```

--

Show current status of all VMs, again:

```bash
% vagrant status
```

--

SSH into the VM:

```bash
% vagrant ssh
```

---

# Directory mapping


.pull-left[
## Host machine

```bash
% ls -al
```
]


.pull-right[
## Guest machine

```bash
$ ls -al  /vagrant
```
]

--

Default mapping rule .red[*]:

```yaml
Vagrant.configure(2) do |config|

  #                         host    guest
  config.vm.synced_folder   "."  ,  "/vagrant"

end
```


.footnote[.red[*] Vagrant calls this feature "[synced folder](https://docs.vagrantup.com/v2/synced-folders/basic_usage.html)".
]

---

# Logout

.pull-right[
## Guest machine

```bash
$ exit
```
]

--
<br clear="all">

.pull-left[


## Host machine
Current status of all VMs:

```bash
% vagrant status
```

Can login again:

```bash
% vagrant ssh
```
]

---

# Shutdown

Shutdown the VM:

```bash
% vagrant halt

% # current VM status?
% vagrant status
```

--

We can power on the default VM, later:

```bash
% vagrant up

% # current VM status?
% vagrant status
```


---

# Destroy

Destroy the VM instance:

```bash
% vagrant destroy

% # current VM status?
% vagrant status
```

--

Since the VM instance has been destroyed altogether, the following power on procedure will take times, as if it has never been `vagrant up` before...

```bash
% vagrant up

% # current VM status?
% vagrant status
```


---

template: inverse

# Snapshot

.footnote[Vagrant plugin: [vagrant-vbox-snapshot](https://github.com/dergachev/vagrant-vbox-snapshot) ]

---

class: center, middle

`% vagrant plugin install  ` [`vagrant-vbox-snapshot`](https://github.com/dergachev/vagrant-vbox-snapshot)


---

## Display all "snapshot" related commands:

```bash
% vagrant snapshot
Usage: vagrant snapshot <command> [<args>]

Available subcommands:
     back
     delete
     go
     list
     take

For help on any individual command run `vagrant snapshot <command> -h`
```

---

# List all saved snapshot(s)

```bash
% vagrant snapshot list
```

---

# Take a snapshot of current VM


- Name your snapshot, e.g., `02/19-08:00`

  ```bash
  % vagrant snapshot take  02/19-08:00
  ```

--

- Check if the snapshot has been saved...

  ```bash
  % # snapshot saved?
  % vagrant snapshot list
  ```

--

- Full usage:

  ```bash
  % vagrant snapshot take -h
  Take snapshot

  Usage: vagrant snapshot take [vm-name] <SNAPSHOT_NAME>
      -h, --help                       Print this help
  ```


---

# Restore from the *latest* snapshot

- List all snapshot(s)...

  ```bash
  % vagrant snapshot list
  ```

- Restore from the latest snapshot:

  ```bash
  % vagrant snapshot back
  ```

--

- Full usage:

  ```bash
  % vagrant snapshot back -h
  Back to current snapshot

  Usage: vagrant snapshot back [vm-name]
      -h, --help                       Print this help
  ```

---

# Restore from a *specific* snapshot

- List all snapshot(s)...

  ```bash
  % vagrant snapshot list
  ```

- Restore from a specific snapshot:

  ```bash
  % vagrant snapshot go  02/19-08:00
  ```

--

- Full usage

  ```bash
  % vagrant snapshot go -h
  Go to specified snapshot

  Usage: vagrant snapshot go [vm-name] <SNAPSHOT_NAME>
      -r, --reload                     Runs 'vagrant reload --no-provision' after restoring snapshot to ensure Vagrantfile config is applied.
      -h, --help                       Print this help
  ```

---

# Delete a specific snapshot

- Full usage

  ```bash
  % vagrant snapshot delete -h
  Delete snapshot (warning: this is a `very slow` operation)

  Usage: vagrant snapshot delete [vm-name] <SNAPSHOT_NAME>
      -h, --help                       Print this help
  ```

---

# Want to learn more?

Read my [Vagrant Tutorial series](http://www.codedata.com.tw/social-coding/vagrant-tutorial-1-developer-and-vm) at CodeData.

.center[.percent90[![Vagrant article logo](http://www.codedata.com.tw/wp-content/uploads/2014/08/VagrantTutorial.jpg)
]]
