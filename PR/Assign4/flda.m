%function fda()
[classNo,classList,testData,trainData,trainLabel] = loadData('image');
classMean = zeros(classNo,size(trainData,2));
scatterW = zeros(size(trainData,2));scatterB = zeros(size(trainData,2));
mean = sum(trainData)/size(trainData,1);
for i = 1:classNo
    classMean(i,:) = sum(trainData(trainLabel==i,:))/sum(trainLabel==i);
    temp = bsxfun(@minus,trainData(trainLabel==i,:),classMean(i,:));
    scatterW = scatterW + (temp'*temp);
    temp = classMean(i,:) - mean;
    scatterB = scatterB + (temp'*temp) * sum(trainLabel==i);
end
[W,D] = eig(scatterB,scatterW);
[~,index] = sort(diag(D),'descend');
W = W(:,index(1:classNo-1));
projTrain = trainData*W;
for i = 1:classNo
    for j = 1:size(testData{i},2)
        projTest{i}{j} = testData{i}{j}*W;
    end
end

projMean = zeros(classNo,classNo-1);
projCov{classNo} = {};
for i = 1:classNo
    fprintf('Class "%s" : Starting Training...\n',classList{i});
    projMean(i,:) = sum(projTrain(trainLabel==i,:))/sum(trainLabel==i);
    projCov{i} = cov(projTrain(trainLabel==i,:));
    fprintf('Class "%s" : Finished Training \n',classList{i});
end
%Confusion Matrix
ConfMat = zeros(classNo);
%Classification Accuracy
Accu(1:classNo) = 0;

disp('Starting Testing...');

for s = 1:classNo
    fprintf('Testing Class "%s"...\n',classList{s});
    for i = 1:size(projTest{s},2)
        likelihood=zeros(1,classNo);
        for j = 1:size(projTest{s}{i},1)
            for k = 1:classNo
                %likelihood(k) = (projTest{s}(i,:)-projMean(k,:))/projCov{k}*(projTest{s}(i,:)-projMean(k,:))'+log(abs(det(projCov{k})));
                %likelihood(k) = -likelihood(k)/2 + log(sum(trainLabel==i)/size(trainLabel,2));
                likelihood(k) = likelihood(k) + log(mvnpdf(projTest{s}{i}(j,:),projMean(k,:),projCov{k}));
            end
        end
        [~,class] = max(likelihood);
        ConfMat(s,class) = ConfMat(s,class) + 1;
    end
end

for s = 1:classNo
    Accu(s) = ConfMat(s,s) / sum(ConfMat(s,:));
end
AvgAccu = sum(diag(ConfMat))/sum(sum(ConfMat));

clc;

disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);
disp('Average Accuracy');
disp(AvgAccu);

clear D W i index scatterB scatterW temp;
%end