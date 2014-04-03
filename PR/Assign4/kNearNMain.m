%K Nearest Neighbour Main

[classNo,classList,testData,trainData,trainLabel] = loadData('image');
K = input('Input No of Nearest Neighbours (K): ');
confMat = zeros(classNo);
for i = 1:classNo
    % Class
    for j = 1:size(testData{i},2)
        % File
        prob = zeros(1,classNo);
        for k = 1:size(testData{i}{j},1)
            % Vector
            prob = prob + kNearN(testData{i}{j}(k,:),trainData,trainLabel',K,classNo);
        end
        [~,class] = max(prob);
        confMat(i,class) = confMat(i,class) + 1;
    end
    fprintf('Classification of class "%s" finished\n',classList{i});
end
accuracy = sum(diag(confMat))/sum(sum(confMat));
disp(confMat);
fprintf('Accuracy = %f\n',accuracy);
clear i j k class classNo classList testData trainData trainLabel prob;