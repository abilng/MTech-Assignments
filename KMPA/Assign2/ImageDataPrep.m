function ImageDataPrep(CompleteData)

DATADIR='../data/Image/';


classIndex = [9,5,17,6,1];
for i=1:5
    %Split the Image dataset in ratio 70:10:20 for Train:Validation:Test 
    class = CompleteData{classIndex(i),1};
    [classSize,~] = size(class);
    index = randperm(classSize);
    class = class(index,:);
    trainEnd = ceil(classSize*0.70);
    valEnd = floor(classSize*0.80);
    trainData = class(1:trainEnd,:);
    valData = class(trainEnd+1:valEnd,:);
    testData = class(valEnd+1:end,:);
    save([DATADIR,'class',int2str(i),'_train.txt'],'trainData'  ,'-ascii');
    save([DATADIR,'class',int2str(i),'_val.txt'],'valData','-ascii');
    save([DATADIR,'class',int2str(i),'_test.txt'],'testData','-ascii');
end


