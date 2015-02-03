@ECHO OFF

set HOSTS=(  main  alice  bob  centos  registry  )

for %%i in %HOSTS% do (
  vagrant up --provision  %%i
  vagrant halt %%i
)
