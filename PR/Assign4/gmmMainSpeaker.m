% Gaussian Mixture Model

[classNo,classList,testData,trainData,trainLabel] = loadData('speaker');

%No of Clusters
%K = zeros(1,classNo);
%for s =1:classNo
%    K(s) = input(['Enter No. of Clusters(Class "' classList{s} '"): ']);
%end
K(1:classNo) = input('Enter No. of Clusters: ');

gmm(1:classNo) = GMM(0);
for s = 1:classNo
    gmm(s) = GMM(K(s));
end

disp('Starting Training...');

for i = 1:classNo
    fprintf('Class %d "%s" : Starting Training...\n',i,classList{i});
    while(1)
        try
            gmm(i).train(trainData(trainLabel==i,:));
            break;
        catch Error
            if (strcmp(Error.identifier,'stats:mvnpdf:BadMatrixSigma'))
                K(i) = K(i) - 1;
                disp(K(i));
                gmm(i).resetK(K(i));
            else
                rethrow(Error);
            end
        end
    end
    fprintf('Class %d "%s": Finished Training \n',i,classList{i});
end


%Confusion Matrix
ConfMatFull = zeros(classNo);
ConfMatNaive = zeros(classNo);
%Classification Accuracy
AccuFull(1:classNo) = 0;
AccuNaive(1:classNo) = 0;

disp('Starting Testing...');

for s = 1:classNo
    %fprintf('Testing Class "%s"...\n',classList{s});
    for i = 1:size(testData{s},2)
        likelihood=zeros(1,classNo);
        for k = 1:classNo
            for j = 1:size(testData{s}{i},1)
                likelihood(k) = likelihood(k) + gmm(k).getLikelihood(testData{s}{i}(j,:));
            end
        end
        [~,class] = max(likelihood);
        ConfMatFull(s,class) = ConfMatFull(s,class) + 1;
        
        likelihood=zeros(1,classNo);
        for k = 1:classNo
            for j = 1:size(testData{s}{i},1)
                likelihood(k) = likelihood(k) + gmm(k).getLikelihood(testData{s}{i}(j,:),true);
            end
        end
        [~,class] = max(likelihood);
        ConfMatNaive(s,class) = ConfMatNaive(s,class) + 1;
    end
end

for s = 1:classNo
    AccuFull(s) = ConfMatFull(s,s) / sum(ConfMatFull(s,:));
    AccuNaive(s) = ConfMatNaive(s,s) / sum(ConfMatNaive(s,:));
end
AvgAccuFull = sum(diag(ConfMatFull))/sum(sum(ConfMatFull));
AvgAccuNaive = sum(diag(ConfMatNaive))/sum(sum(ConfMatNaive));

clc;

%for s =1:classNo
%    disp(['No. of Clusters(Class "' classList{s} '"): ' num2str(K(s))]);
%end

disp('With Full Covariance Matrices')
%disp('Confusion Matrix');
%disp(ConfMatFull);
disp('Classification Accuracy');
disp(AccuFull);
disp('Average Accuracy');
disp(AvgAccuFull);

disp('With Diagonal Covariance Matrices')
%disp('Confusion Matrix');
%disp(ConfMatNaive);
disp('Classification Accuracy');
disp(AccuNaive);
disp('Average Accuracy');
disp(AvgAccuNaive);

% clear all;