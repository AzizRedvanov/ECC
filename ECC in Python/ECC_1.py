from math import *
from Criptosystem_EC import *
from modinverse import *
from partition_of_number import *
from random import *
import time

p = 18467548642013459782465125548763244987000123456875200012456871123154789578425136470000000000000000389
a, b = 0, 3
Xp, Yp = 1, 2
na = 51922968585385449841514984891541964165461620654196846132165464615646546546546464645645984916515949846
nb = 58460365491654968416546548974891651564894651321968489431625168416555159489741654984864362159649846165

Zp = randint(1,p-1)
Xp, Yp = (Xp*Zp)%p, (Yp*Zp)%p

'''y^2*z = x^3 + axz^2 + bz^3 (mod p)
P(Xp,Yp,Zp)
na - private key 1
nb - private key 2

Qa(Xqa,Yqa,Zqa)=naP    -   public key 1  
Qb(Xqb,Yqb,Zqb)=nbP    -   public key 2
(Xa,Ya,Za)=naQb=na*nb*P=nbQa=(Xb,Yb,Zb) <=> (X,Y,Z)-общий ключ'''

Xqa, Yqa, Zqa = multiply_scalar(p,a,Xp,Yp,Zp,na)
Xqb, Yqb, Zqb = multiply_scalar(p,a,Xp,Yp,Zp,nb)

Xa, Ya, Za = multiply_scalar(p,a,Xqb,Yqb,Zqb,na)
Xb, Yb, Zb = multiply_scalar(p,a,Xqa,Yqa,Zqa,nb)

print("\n1 key: (",Xa,";",Ya,";",Za,")")
print("\n2 key: (",Xb,";",Yb,";",Zb,")\n")

'''C1=Qa=naP
   C2= M+naQb
   C2-nbC1=(M+naQb)-nbQa=M + na*nb*P - nb*na*P=M'''

#M = "Как известно, информационные системы способны отображать в себе самые разнообразные явления мироздания, и, стало быть, все явления то-же оказываются потенциальными объектами проектирования. Информационные системы во многих случаях оказываются субъек-тами проектирования, т.е. теми исполнителями, которые осуществляют сам процесс проектирования. Изучая процесс проектирования, мы тем самым в значительной мере занимаемся исследованием информационных систем. Таким образом, между проектированием и информационными си-стемами существуют отношения двоякого рода, и все они важны для ин-форматики. Под системой понимают любой объект, который одновременно рас-сматривается и как единое целое, и как объединенная в интересах достиже-ния поставленных целей совокупность разнородных элементов. Системы значительно отличаются между собой как по составу, так и по главным це-лям. В информатике понятие система широко распространено и имеет множество смысловых значений. Чаще всего оно используется примени-тельно к набору технических средств и программ. Добавление к понятию система слова информационная отражает цель ее создания и функциони-рования. Информационные системы обеспечивают: сбор, хранение, обра-ботку, поиск, выдачу информации, необходимой в процессе принятия ре-шений задач из любой области. Они помогают анализировать проблемы и создавать новые продукты. Информационная система (ИС) – взаимосвязанная совокупность средств, методов и персонала, используемых для хранения, обработки и выдачи информации в интересах достижения поставленной цели. Современные информационные технологии предоставляют широкий набор способов реализации ИС, выбор которых осуществляется на основе требований со стороны предполагаемых пользователей, которые, как пра-вило, изменяются в процессе разработки. Под проектом ИС будем понимать проектно-конструкторскую и тех-нологическую документацию, в которой представлено описание проектных решений по созданию и эксплуатации ИС в конкретной программно-технической среде. Можно выделить следующие основные отличительные признаки проекта как объекта управления: ограниченность конечной цели; ограни-ченность продолжительности; ограниченность бюджета; ограниченность требуемых ресурсов; новизна для предприятия, для которого реализуется проект; комплексность; правовое и организационное обеспечение. Рассматривая планирование проектов и управление ими, необходимо чётко осознавать, что речь идёт об управлении неким динамическим объ-ектом. Поэтому система управления проектом должна быть достаточно гибкой, чтобы допускать возможность модификации без глобальных изме-нений в рабочей программе. Выполнение работ обеспечивается наличием необходимых ресурсов: материалов; оборудования; человеческих ресур-сов. С точки зрения теории систем управления проект как объект управле-ния должен быть наблюдаемым и управляемым, то есть выделяются неко-торые характеристики, по которым можно постоянно контролировать ход выполнения проекта. Кроме того, необходимы механизмы своевременного воздействия на ход выполнения проекта. Под проектированием ИС понимается процесс преобразования входной информации об объекте, методах и опыте проектирования объек-тов аналогичного назначения в соответствии с ГОСТом в проект ИС. С этой точки зрения проектирование ИС сводится к последователь-ной формализации проектных решений на различных стадиях жизненного цикла ИС: планирования и анализа требований, технического и рабочего проектирования, внедрения и эксплуатации ИС."
M = "В последнее время все чаще разработка программ начинается с некоторого предварительного варианта системы. В качестве такого варианта может выступать специально для этого разработанный прототип, либо устаревшая и не удовлетворяющая новым требованиям система."
#M = "The properties and functions of elliptic curves have been studied in mathematics for 150 years. Their use within cryptography was first proposed in 1985, (separately) by Neal Koblitz from the University of Washington, and Victor Miller at IBM. An elliptic curve is not an ellipse (oval shape), but is represented as a looping line intersecting two axes (lines on a graph used to indicate the position of a point). ECC is based on properties of a particular type of equation created from the mathematical group (a set of values for which operations can be performed on any two members of the group to produce a third member) derived from points where the line intersects the axes. Multiplying a point on the curve by a number will produce another point on the curve, but it is very difficult to find what number was used, even if you know the original point and the result. Equations based on elliptic curves have a characteristic that is very valuable for cryptography purposes: they are relatively easy to perform, and extremely difficult to reverse."
print(M)
print("Text length:",len(M))

print("Cipher text:")
t1 = time.clock()
Ma, Mza = EnCode(M,p,Xa,Ya,Za)
t2 = time.clock()
print(Ma,Mza)
print("Text encryption:",t2-t1,"с")
t3 = time.clock()
Mb = DeCode(Ma,Mza,p,Xb,Yb,Zb)
t4 = time.clock()
print()
print(Mb)
print("Text length:",len(Mb))
print("Text decryption:",t4-t3,"с")

