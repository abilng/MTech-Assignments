%Parzen Window Main

[classNo,classList,testData,trainData,trainLabel] = loadData('image');
h = input('Input the Window Size: ');
windowType = input('Input the Window Type(hypersphere(1)/gaussian(2)): ');
confMat = zeros(classNo);
for i = 1:classNo
    % Class
    switch(windowType)
        case 1
            for j = 1:size(testData{i},2)
                % File
                class = parzenWindow(testData{i}{j}, ...
                    trainData,trainLabel',h,classNo,'hypersphere');
                
                confMat(i,class) = confMat(i,class) + 1;
            end
        case 2
            for j = 1:size(testData{i},2)
                % File
                class = parzenWindow(testData{i}{j}, ...
                    trainData,trainLabel',h,classNo,'gaussian');
                confMat(i,class) = confMat(i,class) + 1;
            end
        otherwise
            error('Unknown Type');
    end
    fprintf('Classification of class "%s" finished\n',classList{i});
end
accuracy = sum(diag(confMat))/sum(sum(confMat));
disp(confMat);
fprintf('Accuracy = %f\n',accuracy);
clear i j class classNo classList testData trainData trainLabel;