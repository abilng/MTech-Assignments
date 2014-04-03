function [classNo,classList,testData,trainData,trainLabel] = loadData(datatype)

% LoadData - Load data for problems given the question number as input
% Input - datatype : Type of data to be loaded
%           1. Image
%           2. Linearly seperable dataset
%           ...
% Output - data : Data of different classes as cell array

switch datatype
    case 'image'
        % Load Filelist of the Image Dataset
        % dataPath : Path of Image Dataset
        if exist('../data/nonparametric/image','dir')
            dataPath = '../data/nonparametric/image';
        elseif exist('../data/gmm/image','dir')
            dataPath = '../data/gmm/image';
        else
            dataPath = uigetdir;
        end
        % classList{} : List of Classes
        classList = dir(dataPath);
        classList = {classList(~strncmpi({classList.name},'.',1)).name};
        % classNo : No of Classes
        [~,classNo] = size(classList);
        % classSize() : Size of each Class
        classSize = zeros(1,classNo);
        % fileList{} : List of Files in each Class
        fileList{classNo} = {};
        % K : Percent of Test Data
        K = input('Percent of Test Data: ')/100;
        % trainInd{} : Index of Files in Training for each Class
        trainInd{classNo} = {};
        % testInd{} : Index of Files in Testing for each Class
        testInd{classNo} = {};
        % testData{} : Test Data of each Class
        testData{classNo} = {};
        % trainData : Training Data
        trainData = [];
        % trainLabel : Label of Training Data
        trainLabel = [];
        for i = 1:classNo
            fileList{i} = dir([dataPath '/' classList{i}]);
            fileList{i} = {fileList{i}(~strncmpi({fileList{i}.name},'.',1)).name};
            classSize(i) = size(fileList{i},2);
            % Divide Image Dataset to Train and Test
            Index = randperm(classSize(i));
            % numTest : Number of Test Files per Class
            numTest = round(classSize(i)*K);
            numTrain = classSize(i)-numTest;
            testInd{i} = sort(Index(1:numTest));
            trainInd{i} = sort(Index(numTest+1:classSize(i)));
            for j = 1:numTest
                testData{i}{j} = load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(testInd{i}(j)))));
            end
            % Temporary Variables
            tempLabel = [];
            [p,q] = size(testData{i}{j});
            tempTrain = zeros(numTrain*p,q);
            for j = 1:numTrain
                tempTrain((j-1)*p+1:j*p,:) = load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(trainInd{i}(j)))));
            end
            trainData = [trainData;tempTrain];
            p = size(tempTrain,1);
            tempLabel(1:p) = i;
            trainLabel = [trainLabel tempLabel];
            clear p j tempData tempLabel numTest numTrain Index;
        end
        clear i K dataPath classSize testInd trainInd fileList;
        
    case 'image_flda'
        % Load Filelist of the Speaker Dataset
        % dataPath : Path of Speaker Dataset
        if exist('../data/nonparametric/image','dir')
            dataPath = '../data/nonparametric/image';
        elseif exist('../data/gmm/image','dir')
            dataPath = '../data/gmm/image';
        else
            dataPath = uigetdir;
        end
        % classList{} : List of Classes
        classList = dir(dataPath);
        classList = {classList(~strncmpi({classList.name},'.',1)).name};
        % classNo : No of Classes
        classNo = size(classList,2);
        % classSize() : Size of each Class
        classSize = zeros(1,classNo);
        % fileList{} : List of Files in each Class
        fileList{classNo} = {};
        % K : Percent of Test Data
        K = input('Percent of Test Data: ')/100;
        % trainInd{} : Index of Files in Training for each Class
        trainInd{classNo} = {};
        % testInd{} : Index of Files in Testing for each Class
        testInd{classNo} = {};
        % testData{} : Test Data of each Class
        testData{classNo} = [];
        % trainData : Training Data
        trainData = [];
        % trainLabel : Label of Training Data
        trainLabel = [];
        
        for i = 1:classNo
            fileList{i} = dir([dataPath '/' classList{i}]);
            fileList{i} = {fileList{i}(~strncmpi({fileList{i}.name},'.',1)).name};
            classSize(i) = size(fileList{i},2);
            % Divide Image Dataset to Train and Test
            Index = randperm(classSize(i));
            % numTest : Number of Test Files per Class
            numTest = round(classSize(i)*K);
            numTrain = classSize(i)-numTest;
            testInd{i} = sort(Index(1:numTest));
            trainInd{i} = sort(Index(numTest+1:classSize(i)));
            for j = 1:numTest
                testData{i}(j,:) = makeLine(load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(testInd{i}(j))))));
            end
            % Temporary Variables
            tempTrain = [];
            tempLabel = [];
            for j = 1:numTrain
                tempTrain = [tempTrain;makeLine(load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(trainInd{i}(j))))))];
            end
            trainData = [trainData;tempTrain];
            p = size(tempTrain,1);
            tempLabel(1:p) = i;
            trainLabel = [trainLabel tempLabel];
            clear p j tempData tempLabel numTest numTrain Index;
        end
        clear i K dataPath classSize testInd trainInd fileList;
        
        
    case 'speaker'
        % Load Filelist of the Speaker Dataset
        % dataPath : Path of Speaker Dataset
        if exist('../data/gmm/speaker','dir')
            dataPath = '../data/gmm/speaker';
        else
            dataPath = uigetdir;
        end
        % classList{} : List of Classes
        classList = dir(dataPath);
        classList = {classList(~strncmpi({classList.name},'.',1)).name};
        % classNo : No of Classes
        classNo = size(classList,2);
        % classSize() : Size of each Class
        classSize = zeros(1,classNo);
        % fileList{} : List of Files in each Class
        fileList{classNo} = {};
        % K : Percent of Test Data
        K = input('Percent of Test Data: ')/100;
        % trainInd{} : Index of Files in Training for each Class
        trainInd{classNo} = {};
        % testInd{} : Index of Files in Testing for each Class
        testInd{classNo} = {};
        % testData{} : Test Data of each Class
        testData{classNo} = {};
        % trainData : Training Data
        trainData = [];
        % trainLabel : Label of Training Data
        trainLabel = [];
        
        for i = 1:classNo
            fileList{i} = dir([dataPath '/' classList{i}]);
            fileList{i} = {fileList{i}(~strncmpi({fileList{i}.name},'.',1)).name};
            classSize(i) = size(fileList{i},2);
            % Divide Image Dataset to Train and Test
            Index = randperm(classSize(i));
            % numTest : Number of Test Files per Class
            numTest = round(classSize(i)*K);
            numTrain = classSize(i)-numTest;
            testInd{i} = sort(Index(1:numTest));
            trainInd{i} = sort(Index(numTest+1:classSize(i)));
            for j = 1:numTest
                testData{i}{j} = load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(testInd{i}(j)))));
            end
            % Temporary Variables
            tempTrain = [];
            tempLabel = [];
            for j = 1:numTrain
                tempTrain = [tempTrain;load(char(strcat(dataPath,'/',classList{i},'/',fileList{i}(trainInd{i}(j)))))];
            end
            trainData = [trainData;tempTrain];
            p = size(tempTrain,1);
            tempLabel(1:p) = i;
            trainLabel = [trainLabel tempLabel];
            clear p j tempData tempLabel numTest numTrain Index;
        end
        clear i K dataPath classSize testInd trainInd fileList;
        
    otherwise
        error('Unrecognized Dataset');
end
end