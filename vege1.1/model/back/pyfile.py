import os
import torch
import torch.nn as nn
import torch.nn.functional as  F
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
from torch.utils.data import DataLoader, Dataset
from PIL import Image
import argparse

def classes_txt(root, out_path, num_class=None):
    '''
    write image paths (containing class name) into a txt file.
    :param root: data set path
    :param out_path: txt file path
    :param num_class: how many classes needed
    :return: None
    '''
    dirs = os.listdir(root) # 列出根目录下所有类别所在文件夹名
    if not num_class:		# 不指定类别数量就读取所有
        num_class = len(dirs)
        print(num_class)

    if not os.path.exists(out_path): # 输出文件路径不存在就新建
        f = open(out_path, 'w')
        f.close()
	# 如果文件中本来就有一部分内容，只需要补充剩余部分
	# 如果文件中数据的类别数比需要的多就跳过
    with open(out_path, 'w') as f:
        try:
            end = int(f.readlines()[-1].split('/')[-2]) + 1
        except:
            end = 0
        if end < num_class - 1:
            dirs.sort()
            #dirs = dirs[end:num_class]
            for dir in dirs:
                files = os.listdir(os.path.join(root, dir))
                for file in files:
                    f.write(os.path.join(root, dir, file) + '\n')

class MyDataset(Dataset):
    def __init__(self, txt_path, transforms=None):
        super(MyDataset, self).__init__()
        images = [] # 存储图片路径
        labels = [] # 存储类别名，在本例中是数字
        # 打开上一步生成的txt文件
        with open(txt_path, 'r') as f:
            for line in f:
                #if int(line.split('/')[-2]) >= num_class:  # 只读取前 num_class 个类
                #    break
                line = line.strip('\n')
                images.append(line)
                #print(line.split('\\'))
                labels.append(int(line.split('\\')[-2]))
        self.images = images
        self.labels = labels
        self.transforms = transforms # 图片需要进行的变换，ToTensor()等等
        #self.data_info = self.get_img_info(txt_path)

    def __getitem__(self, index):
        image = Image.open(self.images[index]).convert('RGB') # 用PIL.Image读取图像
        label = self.labels[index]
        if self.transforms is not None:
            image = self.transforms(image) # 进行变换
        return image, label

    def __len__(self):
        return len(self.labels)

class NetSmall(nn.Module):
    def __init__(self):
        super(NetSmall, self).__init__()

        self.conv1 = nn.Conv2d(1, 6, 3) # 3个参数分别是in_channels，out_channels，kernel_size，还可以加padding
        self.pool = nn.MaxPool2d(2, [2,2])
        self.conv2 = nn.Conv2d(6, 16, 3)
        self.conv3 = nn.Conv2d(16, 32, 3)
        self.layer1 = nn.Sequential(nn.Linear(4608, 512), nn.BatchNorm1d(512), nn.ReLU(True))
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
        x = x.view(-1, 4608)
        x = self.layer1(x)
        x = self.layer2(x)
        x = self.layer3(x)
        return x

    '''    
    def forward(self,x):
        x=self.layer1(x)
        x=self.layer2(x)
        x = self.layer3(x)
        #x = self.layer4(x)
        x = self.fc(x)
        x=x.view(x.size(0),-1)
        return x
    '''
def train():
    # 由于我的数据集图片尺寸不一，因此要进行resize，这里还可以加入数据增强，灰度变换，随机剪切等等
    transform = transforms.Compose([transforms.Resize((args.image_size, args.image_size)),
                                    transforms.Grayscale(),
                                    transforms.ToTensor()])

    train_set = MyDataset(args.root + '/train.txt', transforms=transform)
    train_loader = DataLoader(train_set, batch_size=args.batch_size, shuffle=True)
    # 选择使用的设备
    device = torch.device('cpu')

    model = NetSmall()
    model.to(device)
    # 训练模式
    model.train()

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=0.01)
    # 由命令行参数决定是否从之前的checkpoint开始训练
    if args.restore:
        print(args.log_path)
        checkpoint = torch.load(args.log_path)
        model.load_state_dict(checkpoint['model_state_dict'])
        optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        loss = checkpoint['loss']
        epoch = checkpoint['epoch']
    else:
        loss = 0.0
        epoch = 0

    while epoch < args.epoch:
        running_loss = 0.0

        for i, data in enumerate(train_loader):
            # 这里取出的数据就是 __getitem__() 返回的数据
            inputs, labels = data[0].to(device), data[1].to(device)
            #print(labels)
            optimizer.zero_grad()
            outs = model(inputs)
            loss = criterion(outs, labels)
            loss.backward()
            optimizer.step()

            running_loss += loss.item()

            if i % 200 == 199:  # every 200 steps
                print('epoch %5d: batch: %5d, loss: %f' % (epoch + 1, i + 1, running_loss / 200))
                running_loss = 0.0
            # 保存 checkpoint

        print('Save checkpoint...')
        torch.save({'epoch': epoch,
                    'model_state_dict': model.state_dict(),
                    'optimizer_state_dict': optimizer.state_dict(),
                    'loss': loss},
                   args.log_path)
        epoch += 1
    print('Finish training')


def validation():
    transform = transforms.Compose([transforms.Resize((args.image_size, args.image_size)),
                                    transforms.Grayscale(),
                                    transforms.ToTensor()])

    test_set = MyDataset(args.root + '/test.txt', transforms=transform)
    test_loader = DataLoader(test_set, batch_size=args.batch_size)

    device = torch.device('cpu')
    model = NetSmall()
    model.to(device)

    checkpoint = torch.load(args.log_path)
    model.load_state_dict(checkpoint['model_state_dict'])

    model.eval()

    total = 0.0
    correct = 0.0
    running_loss = 0.0
    criterion = nn.CrossEntropyLoss()

    with torch.no_grad():
        for i, data in enumerate(test_loader):
            inputs, labels = data[0].to(device), data[1].to(device)
            #print(labels)
            outputs = model(inputs)
            _, predict = torch.max(outputs.data, 1)
            loss = criterion(outputs, labels)
            #print(predict)
            total += labels.size(0)
            #correct += sum(int(predict == labels)).item()
            correct += (predict == labels).sum().item()
            running_loss+=loss.item()
            if i % 100 == 99:
                print('batch: %5d,\t acc: %f,\t loss: %f' % (i + 1, correct / total,running_loss/200))
                running_loss=0.0
    print('Accuracy: %.2f%%' % (correct / total * 100))


def inference():
    print('Start inference...')
    transform = transforms.Compose([transforms.Resize((args.image_size, args.image_size)),
                                    transforms.Grayscale(),
                                    transforms.ToTensor()])

    f = open(args.root + '/test.txt')
    num_line = sum(line.count('\n') for line in f)
    f.seek(0, 0)
    # 在文件中随机取一个路径
    line = int(torch.rand(1).data * num_line - 10)  # -10 for '\n's are more than lines
    while line > 0:
        f.readline()
        line -= 1
    img_path = f.readline().rstrip('\n')
    f.close()
    label = int(img_path.split('\\')[-2])
    print('label:\t%4d' % label)
    input = Image.open(img_path).convert('RGB')
    input = transform(input)
    # 网络默认接受4维数据，即[Batch, Channel, Heigth, Width]，所以要加1个维度
    input = input.unsqueeze(0)
    model = NetSmall()
    model.eval()
    checkpoint = torch.load(args.log_path)
    model.load_state_dict(checkpoint['model_state_dict'])
    output = model(input)
    #_, pred = torch.max(output.data, 1)
    _, pred = torch.sort(output, descending=True)
    import json
    import codecs

    with codecs.open("char_js.json", "r", "gbk") as f:
        for line in f:
            dic = json.loads(line)
    for i in range(10):
        print('predict:\t%4d' % pred[0][i])
        key = list(dic.keys())[list(dic.values()).index(pred[0][i])]
        print(key)


parse = argparse.ArgumentParser(description='Params for training. ')
# 数据集根目录
parse.add_argument('--root', type=str, default='D:/data_1', help='path to data set')
# 模式，3选1
parse.add_argument('--mode', type=str, default='train', choices=['train', 'validation', 'inference'])
# checkpoint 路径
parse.add_argument('--log_path', type=str, default=os.path.abspath('.') + '/log.pth', help='dir of checkpoints')

parse.add_argument('--restore', type=bool, default=False, help='whether to restore checkpoints')

parse.add_argument('--batch_size', type=int, default=16, help='size of mini-batch')
parse.add_argument('--image_size', type=int, default=64, help='resize image')
parse.add_argument('--epoch', type=int, default=20)
parse.add_argument('--num_class', type=int, default=40, choices=range(10, 3925))
args = parse.parse_args()

if __name__ == '__main__':

    classes_txt(args.root + '/train', args.root + '/train.txt', num_class=args.num_class)
    classes_txt(args.root + '/test', args.root + '/test.txt', num_class=args.num_class)

    if args.mode == 'train':
        train()
    elif args.mode == 'validation':
        validation()
    elif args.mode == 'inference':
        inference()

