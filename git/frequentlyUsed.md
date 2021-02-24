# GIT COMMAND MEMOIRE

This memoire records some frequenly used git commands used while coding in the 
VS 2019 Community Environment.

Targets of this memoire:
1. ����� vs �жԱ�2���ļ��Ĳ�ͬ
2. ����� vs �жԱ�2����֧�Ĳ�ͬ
3. ����� vs �жԱ�2���ύ�Ĳ�ͬ

* * *

## 0 Basic git commands

�� Developer PowerShell for VS 2019 �н�·���û������زֿ⣬��ִ�������������򵥵���Զ�ֿ̲����͸��£�8xiaomi12

```shell
chcp 437

git status

git clone https://gitee.com/someones/somerepo.git

git push origin_gitee master
```

ȥ���Ѿ��йܵ��ļ�
```git
git rm -r --cached filename
```


### 0.1 git branch

```git
git branch -al                              // �鿴���غ�Զ�̵����з�֧

git add test.txt                            // �����һ�����ļ�test.txt�� Git
git commit -m "add test.txt"    // �ύ��ӵ��ļ�
rm test.txt                                 // ɾ���������е��ļ�
git rm test.txt                             // ɾ�����е��ļ�
git commit -m "remove test.txt"     // �ύɾ��
git checkout -- test.txt                // �Ӱ汾���лָ��ļ���������
```

### 0.2 git reset


��git push��ʱ����ʱ�����ǻ���취����git commit������

1���ҵ�֮ǰ�ύ�� git commit �� id

```git log``` �ҵ���Ҫ������id

2��git reset �Chard id ��ɳ���, ͬʱ������ָ���ǰһ commit_id ��Ӧ
�İ汾 

3��git reset id ��ɳ��� git commit ������δpush��Զ�ֿ̲⣬���ǲ���
**�����޸Ľ��г���**������ֱ��ͨ�� git commit �����ύ�Ա��ش�����޸�


## 1 compare two files

�� VS �Ա������ļ���Ҫʹ�ñȶԹ��ߣ��ù��߷��� TeamFoundation �ļ����·����
D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\vsDiffMerge.exe ��

����� cmd ��������Աȹ�������Ҫ��������·�������ʹ�� Developer PowerShell for VS 2019 
��ֻ����������Ĵ��룺
```
vsDiffMerge.exe file1 file2
```
���� file1 file2�ֱ��ǽ��жԱȵ������ļ������к���Կ���������� VisualStudio �����ж�
�����ļ����жԱȣ��ԱȽ������ʾ�ǳ�ֱ�ۡ�

## 2 compare two branches

���ʹ�õ��� Powershell ����ô�������� cmd ���������п��Կ����Ա��ļ��ܺ��ã���ô�� git ʹ�õ�Ĭ�ϱȽϷ�֧��
```
git difftool developer master
```
�Ϳ��ԱȽ�������֧�����˲�����Ҫ���� VS ����Ӧ�Ĺ��̡�

![diff in powershell](images/diffInPowerShell.PNG)

��Ϊ������������򵥼�¼����ԱȽ����������һ�����ӣ�

| �ļ� | �������� |
| --- | --- |
| MeshLab/src/common/filterparameter.h | �����ע�� |
| MeshLab/src/common/mlapplication.h | ������Ӧ�ó��������ַ��� |
| MeshLab/src/meshlab/mainwindowt.h | 5����Ҫ�Ķ� |
| MeshLab/src/meshlabplugins/filter_ssynth/filter_ssynth.cpp | 1���Ķ�, �����ĵ���ʽfilter |
| MeshLab/src/meshlabplugins/io_ctm/io_ctm.cpp | importFormat & exportFormat |
| MeshLab/src/meshlabplugins/io_expe/export_xyz.h | save mesh |
| MeshLab/src/meshlabplugins/io_expe/io_expe.cpp | file type can be imported/exported |
| MeshLab/src/meshlabplugins/io_json/io_json.cpp | ���λ���json��io |
| meshlab_full.sln | UID �ı� |
| vcglib/vcg/complex/algorithms/pointcloud_normal.h | �����ע�� |

## 3 compare two commits

git reflog �鿴 hash id ��
git difftool srcID dstID

��Ϊ������������򵥼�¼����ԱȽ����������һ�����ӣ�

| �ļ� | �������� |
| --- | --- |
| MeshLab/src/meshlab/mainwindow.h | ���� quantizeDepth ���� |
| MeshLab/src/meshlab/mainwindow_RunTime.cpp | ʵ���������������� |


