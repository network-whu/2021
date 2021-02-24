
# gitee ����/��� SSH ��Կ
___

[�μ����ư������ĵ�����ĵ�](https://gitee.com/help/articles/4181#article-header0)

## 1. SSH ��Կ������

�����ṩ�˻���SSHЭ���Git������ʹ��SSHЭ����ʲֿ�ֿ�֮ǰ��
��Ҫ�����ú��˻�/�ֿ��SSH��Կ��

����ʹ�� win10 �� **power shell** ִ���������������� sshkey:

```c
chcp 437

ssh-keygen -t rsa -C "someone@whu.edu.cn" 
# Generating public/private rsa key pair...
```

���������Ч�����£�

![ssh-keygen](images/ssh-keygen.PNG)

ִ�еĽ������ ~/.ssh/ �ļ����������� id_rsa �� id_rsa.pub �����ļ���
���� id_rsa ��˽Կ���� id_rsa.pub �ǹ�Կ���������������Կ�Ĺ������������ļ�����
������ڵ�ǰ�ļ��������������������ļ�����Ӧ��˽Կ�͹�Կ����ʱΪ���� ssh ��˳��
�� gitee ����ͨ�ţ�����Ҫ��˽Կ������ ~/.ssh/ �ļ����²�����Ϊ id_rsa��
��Ȼ��������

ʹ�� cat �������鿴һ�����ɵ� rsa ��Կ��������£�

![cat_id_rsa.pub](images/cat_someone.pub.PNG)

## 2. ��������վ��Ӳֿ⹫Կ�����˻���Կ

### 2.1 ��Ӳֿ⹫Կ
�������ɺ�� ssh key��ͨ���ֿ���ҳ ������->������Կ����->����Ӳ���Կ����
������ɵ� public key ��ӵ��ֿ��С�

����Կ������ֻ���ķ�ʽ���ʲֿ⣬��Ҫ���ڲֿ��������������Ĳ����ϣ�
��ȥHTTP��ʽÿ�β�����Ҫ�����������ͨSSH��ʽ���Ĳ�С���޸Ĳֿ������鷳��
����Կ���ú�Ļ�����ֻ֧��clone��pull��ֻ��������
�������Ҫ�Բֿ����д����������Ӹ��˹�Կ��

### 2.2 ��Ӹ����˻���Կ
���˹�Կ����ӷ�����

������ϽǸ����˻��е����ã�Ȼ��������ȫ���á��еġ�SSH ��Կ���������ɵĹ�Կճ����ȥ��ȷ����
��ʱ��Ҫ�����˺ŵ����롣

�����ɺ��� powershell ������
```c
ssh -T git@gitee.com
```
�������������ʾ�������� ssh ��Կ��ӳɹ�

![ssh_rsa_success](images/ssh_rsa_success.PNG)
(provihell... What the hell?)

### 2,3 �����Կ����Ľ������

�����������������Ϣ��˵������
```c
git@gitee.com: Permission denied (publickey).
```
��������û�н�˽Կ������ ~/.ssh/ �ļ����²�����Ϊ id_rsa����һ��������������� SSH 
��Կ����û��ʹ������ gitee �˻��ϵĵ�¼���䣬Ҳ���ܵ������ƴ���

�μ� <https://blog.csdn.net/weixin_43889439/article/details/92760952>

����� git push ʱ�����û���������������ʱ����ܲ�����Կ�����⡣
������ win10 ��ƾ�ݹ������ж� windows ƾ���е� git:https://gitee.com �����޸ģ�
���û��������붼��ȷ��д��

gitee ����Կ���÷������������ؼ�ģ�� github���й� github �� rsa ��Կ���÷����μ���
[github ����ssh��Կ](https://www.jianshu.com/p/33ce73e3cbfe) <br>
�Ǹ� does not provihell access (�� 2.2 ����沿��) Ӧ���� does not provide shell access�� ģ�³��˵�覴á�



