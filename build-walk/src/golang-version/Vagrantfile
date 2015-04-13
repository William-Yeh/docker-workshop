Vagrant.configure(2) do |config|
  config.vm.box = "williamyeh/ubuntu-trusty64-docker"

  config.vm.provision "shell", inline: <<-SHELL
    cd /vagrant
    ./build.sh
  SHELL
end
