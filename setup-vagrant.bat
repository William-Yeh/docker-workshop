@ECHO OFF

set HOSTS=(  main  centos  registry  )

for %%i in %HOSTS% do (
  vagrant up --provision  %%i
  vagrant halt %%i
)
