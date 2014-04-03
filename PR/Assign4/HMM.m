% Load Filelist of the Handwritten Dataset
[classNo, classList, data] = hmmData();
% classSize() : Size of each Class
classSize = zeros(1,classNo);
% K : Percent of Test Data
K = input('Percent of Test Data: ')/100;
% trainInd{} : Index of Files in Training for each Class
trainInd{classNo} = {};
% testInd{} : Index of Files in Testing for each Class
testInd{classNo} = {};
% testData{} : Test Data of each Class
testData{classNo} = {};
% trainData : Training Data
trainData{classNo} = {};
kmData = [];

for i = 1:classNo
    classSize(i) = size(data{i},2);
    % Divide Image Dataset to Train and Test
    Index = randperm(classSize(i));
    % numTest : Number of Test Files per Class
    numTest = round(classSize(i)*K);
    numTrain = classSize(i)-numTest;
    testInd{i} = sort(Index(1:numTest));
    trainInd{i} = sort(Index(numTest+1:classSize(i)));
    for j = 1:numTest
        testData{i}(j) = data{i}(testInd{i}(j));
    end
    tempData = [];
    for j = 1:numTrain
        trainData{i}(j) = data{i}(trainInd{i}(j));
        tempData = [tempData;cell2mat(data{i}(trainInd{i}(j)))];
    end
    kmData = [kmData;tempData];
    clear j numTest numTrain Index tempData;
end

K = input('Enter No. of Clusters: ');
km = KmeansCluster(K);
km.train(kmData);

for s = 1:classNo
    trainlabel = {};
    for i = 1:size(trainData{s},2)
        labeldata = trainData{s}{i};
        [n,~] =size(labeldata);
        label = zeros(1,n);
        for j = 1:n
            label(j) = km.getLabel(labeldata(j,:))-1;
        end
        trainlabel{i} = label;
    end
    trainLabel{s} = trainlabel;
end

for s = 1:classNo
    file = fopen(['hmm/train' num2str(s) '.txt'],'w');
    for i = 1:size(trainData{s},2)
        fprintf(file,'%d ',trainLabel{s}{i});
        fprintf(file,'\n');
    end
    fclose(file);
end

for s = 1:classNo
    testlabel = {};
    for i = 1:size(testData{s},2)
        labeldata = testData{s}{i};
        [n,~] =size(labeldata);
        label = zeros(1,n);
        for j = 1:n
            label(j) = km.getLabel(labeldata(j,:))-1;
        end
        testlabel{i} = label;
    end
    testLabel{s} = testlabel;
end

for s = 1:classNo
    file = fopen(['hmm/test' num2str(s) '.txt'],'w');
    for i = 1:size(testData{s},2)
        fprintf(file,'%d ',testLabel{s}{i});
        fprintf(file,'\n');
    end
    fclose(file);
end

x = [];
for s =1:classNo
    x(s) = input(['Enter No. of States(Class ' num2str(s) '): ']);
end
y = 1/K;

for s = 1:classNo
    file = fopen(['hmm/test' num2str(s) '.hmm.seq'],'w');
    fprintf(file,'states: %d\nsymbols: %d\n\n',x(s),K);
    for j = 1:(x(s)-1)
        fprintf(file,'0.5');
        for i = 1:K
            fprintf(file,'\t%d',y);
        end
        fprintf(file,'\n');
        fprintf(file,'0.5');
        for i = 1:K
            fprintf(file,'\t%d',y);
        end
        fprintf(file,'\n');
        fprintf(file,'\n');
    end
    fprintf(file,'1.0');
    for i = 1:K
        fprintf(file,'\t%d',y);
    end
    fprintf(file,'\n');
    fprintf(file,'0.0');
    for i = 1:K
        fprintf(file,'\t%d',y);
    end
    fclose(file);
end

for s = 1:classNo
    system(['./train_hmm hmm/train' num2str(s) '.txt hmm/test' num2str(s) '.hmm.seq .01']);
end

ConfMat = zeros(classNo);
Accu = zeros(1,classNo);
for i = 1:classNo
    picout = [];
    for j = 1:classNo
        system(['./test_hmm hmm/test' num2str(i) '.txt hmm/train' num2str(j) '.txt.hmm']);
        out = load('alphaout');
        picout = [picout ; out];
    end
    [~,n] = size(picout);
    for j = 1:n
        [~,class] = max(picout(:,j));
        ConfMat(i,class) = ConfMat(i,class) + 1;
    end
end
system('rm alphaout');

for s = 1:classNo
    Accu(s) = ConfMat(s,s) / sum(ConfMat(s,:));
end
AvgAccu = sum(diag(ConfMat))/sum(sum(ConfMat));

clc;

disp(['No. of Clusters: ' num2str(K)]);
disp(['No. of Symbols: ' num2str(K)]);

for s =1:classNo
    disp(['No. of States(Class ' num2str(s) '): ' num2str(x(s))]);
end

disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);
disp('Average Accuracy');
disp(AvgAccu);

clear all;