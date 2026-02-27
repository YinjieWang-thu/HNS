#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 输出包含 Sigma+ 粒子的所有事件（包括事件内全部粒子）

input_file = "phase.dat"#"events_3particles.dat"  "phase.dat"
output_file = "lambdaevents.dat"

lambda_pid = "3122"
proton_pid = "2212"
Kaon_pid = "321"
sigma_pid = "3222"  # 可选：包含 Σ+ 粒子
Cascade_pid = "3312"

with open(input_file) as f, open(output_file, "w") as fout:
    event_lines = []
    has_lambda = False
    has_proton = False
    has_kaon = False
    has_sigma = False  
    has_Cascade = False
    for line in f:
        if line.startswith("#"):
            # 处理上一个事件
            if event_lines and has_Cascade:
                #event_lines and has_sigma and has_kaon:
                n_particles = len([l for l in event_lines if not l.startswith("#")])
                #if n_particles == 3:
                fout.writelines(event_lines)
            # 新事件开始
            event_lines = [line]
            has_lambda = False
            has_proton = False
            has_kaon = False
            has_sigma = False 
            has_Cascade = False
        else:
            event_lines.append(line)
            if lambda_pid in line.split()[1]:  # 第2列是PDG ID
                has_lambda = True
            if proton_pid in line.split()[1]:  # 第2列是PDG ID
                has_proton = True
            if Kaon_pid in line.split()[1]:  # 第2列是PDG ID
                has_kaon = True
            if sigma_pid in line.split()[1]:  # 第2列是PDG ID
                has_sigma = True
            if Cascade_pid in line.split()[1]:  # 第2列是PDG ID
                has_Cascade = True
    # 文件末尾事件
    if event_lines and has_Cascade:
        #event_lines and has_sigma and has_kaon:
        n_particles = len([l for l in event_lines if not l.startswith("#")])
        #if n_particles == 3:
        fout.writelines(event_lines)

print(f"已输出所有包含Cascade-的事件到: {output_file}")


