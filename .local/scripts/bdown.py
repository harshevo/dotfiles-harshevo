#!/bin/python3

import subprocess

temp_dir = "/home/harshevo/brightness_control.txt"

def notify(message):
    subprocess.run(["notify-send",  message], check=True)

def write_tmp_bg(file_path, value):
    try:
        subprocess.run(f"echo {value} | cat > {file_path}", shell=True, check=True)
    except Exception as e:
        notify(e)
        return

def read_tmp_bg(file_path):
    try:
        result = subprocess.run(f"cat {file_path}", shell=True, check=True, capture_output=True, text=True)
        number = int(result.stdout.strip())
        return number
    except subprocess.CalledProcessError as e:
        notify(e)


def dec_bg():
    init_value = read_tmp_bg(temp_dir)
    curr_value = 2
    if init_value and init_value >= 11:
        curr_value = init_value - 10
        write_tmp_bg(temp_dir, curr_value)
    else:
        return
    command = f"ddcutil setvcp 10 {curr_value} --display 1"  
    try:
        subprocess.run(command, shell=True, check=True)
        notify(f"Brightness set to - {curr_value}")
    except subprocess.CalledProcessError as e:
        print(f"Command failed with error: {e}")

dec_bg()

