function [avgPre,avgRec,avgSpe,avgFmea,totAcc] = fMea(confMat)
% Function to calculate Accuracy, Precision, Recall, F Measure
% Input : confMat - Confusion Matrix
disp('Confusion Matrix');
disp(confMat);
n = size(confMat,1);
pre = zeros(1,n);
rec = zeros(1,n);
fmea = zeros(1,n);
spe = zeros(1,n);
totAcc= sum(diag(confMat))/sum(sum(confMat));
for i = 1:n
    pre(i) = confMat(i,i)/sum(confMat(:,i));
    rec(i) = confMat(i,i)/sum(confMat(i,:));
    fmea(i) = 2*pre(i)*rec(i)/(pre(i)+rec(i));
    temp = confMat;
    temp(i,:) = [];
    den = sum(sum(temp));
    temp(:,i) = [];
    num = sum(sum(temp));
    spe(i) = num/den;
    %fprintf('Precision (Class %d): %d\n',i,pre(i)*100);
    %fprintf('Recall or Sensitivity (Class %d): %d\n',i,rec(i)*100);
    %fprintf('Specificity (Class %d): %d\n',i,spe(i)*100);
    %fprintf('F-Measure (Class %d): %d\n\n',i,fmea(i)*100);
end
avgPre = sum(pre)/n;
avgRec = sum(rec)/n;
avgFmea = sum(fmea)/n;
avgSpe = sum(spe)/n;
%fprintf('Average Precision = %f\n',avgPre*100);
%fprintf('Average Recall = %f\n',avgRec*100);
%fprintf('Average Specificity = %f\n',avgSpe*100);
%fprintf('Average F-Measure = %f\n',avgFmea*100);
%fprintf('Total Accuracy = %f\n',totAcc*100);
fprintf('Precision = %f\n',avgPre*100);
fprintf('Recall = %f\n',avgRec*100);
fprintf('Specificity = %f\n',avgSpe*100);
fprintf('F-Measure = %f\n',avgFmea*100);
fprintf('Accuracy = %f\n',totAcc*100);
end