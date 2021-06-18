'''
import os
import numpy as np
import struct
from PIL import Image


data_dir = 'D:\ChromeDownloads'
train_data_dir = os.path.join(data_dir, 'Gnt1.1TrainPart1')
test_data_dir = os.path.join(data_dir, 'Gnt1.1test')


def read_from_gnt_dir(gnt_dir=train_data_dir):
    def one_file(f):
        header_size = 10
        while True:
            header = np.fromfile(f, dtype='uint8', count=header_size)
            if not header.size: break
            sample_size = header[0] + (header[1]<<8) + (header[2]<<16) + (header[3]<<24)
            tagcode = header[5] + (header[4]<<8)
            width = header[6] + (header[7]<<8)
            height = header[8] + (header[9]<<8)
            if header_size + width*height != sample_size:
                break
            image = np.fromfile(f, dtype='uint8', count=width*height).reshape((height, width))
            yield image, tagcode
    for file_name in os.listdir(gnt_dir):
        if file_name.endswith('.gnt'):
            file_path = os.path.join(gnt_dir, file_name)
            with open(file_path, 'rb') as f:
                for image, tagcode in one_file(f):
                    yield image, tagcode
char_set = set()
for _, tagcode in read_from_gnt_dir(gnt_dir=train_data_dir):
    tagcode_unicode = struct.pack('>H', tagcode).decode('gbk')
    char_set.add(tagcode_unicode)
char_list = list(char_set)
char_dict = dict(zip(sorted(char_list), range(len(char_list))))
print(len(char_dict))
import pickle
import json
f = open('char_dict', 'wb')
pickle.dump(char_dict, f)
f.close()
char_js = json.dumps(char_dict)
fileObject = open('char_js.json', 'w')
fileObject.write(char_js)
fileObject.close()
'''
'''
import json
import codecs

data = []
with codecs.open("char_js.json", "r","gbk") as f:
    for line in f:
        dic = json.loads(line)
        data.append(dic)
        print(json.dumps(dic, indent=4, ensure_ascii=False))
'''
import torch
import torch.nn as nn
import torch.nn.functional as  F
import torchvision

class NetSmall(nn.Module):
    def __init__(self):
        super(NetSmall, self).__init__()

        self.conv1 = nn.Conv2d(1, 16, 3) # 3个参数分别是in_channels，out_channels，kernel_size，还可以加padding
        self.pool = nn.MaxPool2d(2, [2,2])
        self.conv2 = nn.Conv2d(16, 32, 3)
        self.conv3 = nn.Conv2d(32, 64, 3)
        self.layer1 = nn.Sequential(nn.Linear(9216, 512), nn.BatchNorm1d(512), nn.ReLU(True))
        self.layer2 = nn.Sequential(nn.Linear(512, 84), nn.BatchNorm1d(84), nn.ReLU(True))
        self.layer3 = nn.Sequential(nn.Linear(84, 3925), nn.BatchNorm1d(3925), nn.ReLU(True))
        #self.fc1 = nn.Linear(9216, 512)
        #self.fc2 = nn.Linear(512, 84)
        #self.fc3 = nn.Linear(84, 3925) # 命令行参数，后面解释

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = F.relu(self.conv3(x))
        #print(x.shape)
        x = x.view(-1, 9216)
        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        return x

device = torch.device('cpu')
model = NetSmall()
model.to(device)

checkpoint = torch.load("log.pth")
model.load_state_dict(checkpoint['model_state_dict'])

x = torch.rand(16, 1, 64, 64)
ts = torch.jit.trace(model.eval(), x)
ts.save('model.pt')