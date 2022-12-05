import matplotlib.pyplot as plt

seq = [0.00052789, 0.0005, 0.00597453, 0.00596639, 0.0931611, 0.157865, 1.12691]

ct_5 = [0.00030153, 0.000234934, 0.000227213, 0.000294992, 0.00267604, 0.000776429, 0.000783397]
ct_4 = [0.000277842, 0.000287156, 0.000368432, 0.000310311, 0.00635734 , 0.000776986, 0.000967638]
ct_15 = [0.0029168, 0.00181365, 0.00164153, 0.00163852, 0.0045125, 0.00169129, 0.00160329]
ct_20 = [0.00610759, 0.00368014, 0.00318394, 0.00252199, 0.00271443, 0.00287231, 0.00272209]
ct_40 = [0.0417481, 0.0221153, 0.0202444, 0.0153848, 0.0191523, 0.0162056, 0.0139478]
ct_50 = [0.0795578, 0.0401069, 0.0396937, 0.0302709, 0.0355091, 0.0304704, 0.0251839]
ct_100 = [0.576879, 0.322412, 0.268374, 0.232849, 0.211548, 0.182529, 0.172701]
threads = [2, 4, 6, 8, 12, 16, 20]

speedup_ct_5 = [seq[0]/item for item in ct_5]
speedup_ct_4 = [seq[1]/item for item in ct_4]
speedup_ct_15 = [seq[2]/item for item in ct_15]
speedup_ct_20 = [seq[3]/item for item in ct_20]
speedup_ct_40 = [seq[4]/item for item in ct_40]
speedup_ct_50 = [seq[5]/item for item in ct_50]
speedup_ct_100 = [seq[6]/item for item in ct_100]


plt.plot(threads, speedup_ct_5, color='red', label='5')
plt.plot(threads, speedup_ct_4, color='blue', label='4')
plt.plot(threads, speedup_ct_15, color='green', label='15')
plt.plot(threads, speedup_ct_20, color='orange', label='20')
plt.plot(threads, speedup_ct_40, color='magenta', label='40')
plt.plot(threads, speedup_ct_50, color='black', label='50')
plt.plot(threads, speedup_ct_100, label='100')


plt.xlabel('Número de Threads')
plt.ylabel('Speedup')
plt.legend(title = "Número de Cidades")
#plt.show()
plt.savefig('comparison_speedup.png')




