Instruções de Instalação e Execução

1. Nas propriedades do Projeto setar os seguintes campos:
- Target Plataform Version: 10 (alguma coisa)
- Plataform Toolset: Visual Studio 2015 (v140)

2. Setar a flag _SCL_SECURE_NO_WARNINGS:
- In solution explorer, right click the project, select "properties". The project property page will open. 
Expand the ">C/C++" entry in the tree on the left and select "Preprocessor" under that. 
The top entry in the right pane should be "Preprocessor Definitions". In that edit box, 
add _SCL_SECURE_NO_WARNINGS, separating it from the other entries with a ;

Fonte: https://stackoverflow.com/questions/25046829/what-does-use-d-scl-secure-no-warnings-mean

3. Link Lib e include
Set the VS Project include and lib folders to point to the directories
Right click the CommandCenter project in VS2017
Select "Properties"
Select the correct configuration that you want to build in the top left ("Debug")
Select the target platform you want to build (x64)
Select "VC++ Directories" on the left
Select the "Include Directories" option in the table on the right
Click the dropdown arrow on the right and click Edit...
Modify the existing directory entry to point to your (SC2API)/include directory
Select the "Library Directories" option in the table on the right
Click the dropdown arrow on the right and click Edit...
Modify the existing directory entry to point to your (SC2API)/lib directory
From the "Build" menu, click "Build Solution"

Fonte: https://github.com/davechurchill/CommandCenter

