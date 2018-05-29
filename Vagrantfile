Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial64"
  config.vm.synced_folder ".", "/home/vagrant/forest"
  config.vm.provider "virtualbox" do |vb|
    vb.memory = "1024"
    vb.cpus = "4"
  end
  config.vm.provision "shell", path: "bootstrap.sh"
end
