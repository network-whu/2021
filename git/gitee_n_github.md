# ��ν����� git �ֿ�ͬ�����͵�Զ�̵� gitee �� github �ֿ�

Windows 10 �½����زֿ����͵����Զ�ֿ̲ⷽ���ܶ࣬���γ������Ƽ�2�ַ�����
�����ڱ��γ̵�ʵ����Ϸֱ���������ַ�����������Ӧ��ʵ�����д��ʵ�鱨�档

�ڽ��������ʵ��֮ǰ����Ҫ���� gitee �� github �Ϸֱ𴴽�һ���ֿ���ͬ���㱾�زֿ��е����ݡ�
��Ϊ�������ֿ���Ӻ���Կ��������ͬ���μ�[ʹ�� ssh-key](ssh_gitee.md)�����Ա㽨�� SSH ������������Ӧ��Զ�ֿ̲⡣
�������Ǽ������������õ������ֿ�ֱ�Ϊ��
1. https://gitee.com/someone/some_repo.git
2. https://github.com/someone/some_repo.git

## 1 ʹ�������й���

�����ʹ�� Win10 �Դ��� Windows PowerShell ���� Visual Studio �Դ��� Developer PowerShell.
�� Developer PowerShell �����ַ�ʽ��
1. ����˵��� View��Ȼ���� Terminal
2. ����˵��� Tools��Ȼ���� Command Line�����ŵ�� Developer PowerShell

���������½���Ҫ���͵ı��زֿ����ڵ��ļ���
(�����ʹ�� Developer PowerShell �ҵ�ǰ VS ���򿪵��ļ��о��Ǳ��زֿ����ڵ�λ��, ���������µ�·���Զ�����Ҫ���͵ı��زֿ�)��
�������� git status �鿴һ�µ�ǰ��״̬��

���� gitee �� github Զ�ֿ̲⣨��Ҫ�����زֿ����͵��������ֿ⣩
```shell
git remote add origin_gitee https://gitee.com/someone/some_repo.git
git remote add origin_github https://github.com/someone/some_repo.git
```
��������Ϊ���زֿⴴ����������Զ�ֿ̲�����ӣ����ֱַ�Ϊ origin_gitee �� origin_github 
(��Ҳ����ȡΪ��������, ��ͨ��ȱʡ������Ϊ origin)��

������ɱ��ص� commit ����Ϳ�����Զ�ֿ̲� push �ˡ������ص�ǰ��֧���͵� gitee �ϵ� master ��֧:
```shell
git push -u origin_gitee master
```

�����ص�ǰ��֧���͵� github �ϵ� master ��֧:
```shell
git push -u origin_github master
```
���ҽ�����ʵ����̷ֱ��ͼ��������ͼ��ӵ����ʵ�鱨���С�


## 2 ʹ�� VS �е� Team Explorer ���湤��

��ʹ�� VS �� Open Folder ���㱾�زֿ����ڵ�Ŀ¼��Ȼ��� Team Explorer �������(��� View ���ٵ�� Team Explorer)��
��� Home ���ٵ�� Setting, ���� git ��ǩ�µ�� Repository Settings ������������µĽ��棺

![repository settings](images/repo_settings.PNG)

����·�����ɫ�� Add Ϊ���زֿⴴ����Զ�ֿ̲�����ӣ������ҷֱ𴴽��� origin �� gitee��origin_github �� github����
�����ͨ�� Edit ���޸�, ͨ�� Remove ��ɾ����Զ�ֿ̲�����ӡ�

���ӽ����ú����ǾͿ���ѡ�񽫵�ǰ�ύ���͵���ͬ��Զ�ֿ̲⡣��� Home ���� Sync ���������½��棺

![repository sync](images/home_sync.PNG)

�ٵ�� Push �ұߵ����������Σ���ʱ����Զ�ֿ̲����ӵ�ѡ����棬����ѡ��ͬ��Զ�ֿ̲����Ӽ���֧:

![push to remote](images/push_remote.PNG)

��ͼ��ѡ����� origin_github���ٵ�� Push �Ϳ��Խ������ύ���͵���ѡ���Զ�����Ӽ���ѡ��֧��
���Ҫ�ύ��������ͬ��Զ�ֿ̲⣬�����ѡ��� Push ��Ҫ�ֱ������Σ�

���ˡ�Զ�ֿ̲�ͬ��ʵ��͵�����������������κ����⣬�뽫�����ͼ����������Ľ������һ��д�����ʵ�鱨�档


## 3 ʹ�� VS2019 �е� Team Explorer���д���ͬ��ʱ���ܳ��ֵ����⼰�������
### ����һ��
![problem3](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/problem1.png)

�ڳ���ʹ��git������Ŀ�İ汾����ʱ�������pullһ����Ŀ���������������Ĵ�����ʾ��
ԭ�������
��������û������Gitee��SSH��Կ����δ����SSH��Կ������£�����ʹ��git clone Gitee�ϵ���Ŀ�����ǲ���git push��Ŀ��Gitee�ϣ������push��Ŀ��Gitee����ô��������SSH��Կ�����ɹ�Կ�����ù�Կ�İ취�����Բο�Gitee������������£�����������ϸ�Ľ���https://gitee.com/help/articles/4191 ��

����취��

1������SSH��Կ

`ssh-keygen -t rsa -C "xxxxx@xxxxx.com"`  
![SSH��Կ](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/SSHkey.png)

�ҵ���Ӧ��Ŀ¼��

![id_rsaĿ¼](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/id_rsalog.png)

�ҵ�gitee�������ã�

![Gitee����](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/Gitee_setting.png)

�������֮����git push ��ʱ�򣬷��ֻ��ǻ᣺

![again](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/again.png)

�����������̨������ǰʹ�ù�git�����Ա�����˺ź������������˵ģ�������Ҫ�����޸��˺ź����룬�������£�

1.����������

2.ѡ���û��˻�

3.ѡ��������ƾ��

4.ѡ��Windowsƾ��

5.ѡ��git������û���Ϣ

6.ѡ��༭���߽���ɾ������

7.���

��һ����

![��һ��](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/first.png)

�ڶ�����

![�ڶ���](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/second.png)

��������

![������](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/third.png)

�޸����֮���OK�ˡ�

### �������
![problem2](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/problem2.png)

���������
����������
�û��˺ţ�ѡ���������ƾ��

![�������](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/control_table.png)

�޸�ƾ��

![�޸�ƾ��1](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/proof1.png)

�û���Ϊ�ֻ���/����������Ϊ��¼����

![�޸�ƾ��2](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/proof2.png)

�޸���ɺ󣬱��漴��

![����](https://gitee.com/wuhanuniversity/win-principle-2020/raw/master/git/images/save.png)