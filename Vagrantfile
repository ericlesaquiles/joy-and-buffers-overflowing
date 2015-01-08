# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ffuenf/ubuntu-14.10-server-amd64"
  config.vm.provision :shell,
    inline: "cd /vagrant && sudo ./base-configuration.sh"
end
