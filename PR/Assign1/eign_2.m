close all
clear all
clc

IMGPATH = 'C:\Users\abil\Documents\PR\Yogi.gif';
[inImage,map] = imread(IMGPATH);
inImage = ind2rgb(inImage, map);
inImage=rgb2gray(inImage);

inImageD=im2double(inImage);

[M,N]=size(inImageD);
if M ~=N
    printf('A is not sq. Matrix');
    exit;
end;


% decomposing the image into Eign values and Eigen Vectors
[Evector,Evalue] = eig(inImageD);


%Sort Evector and Evalue
sortedEv=diag(sort(diag(Evalue),'descend')); 
[c, ind]=sort(diag(Evalue),'descend');
Evector=Evector(:,ind);
Evalue = sortedEv;

invEv = inv(Evector);

minEVal = input('Enter the minimum number of Eign Value:');
step = input('Enter the step of Eign Value:');
maxEVal = input('Enter the max number of Eign Value:');

if(maxEVal>N), maxEVal = N; end;

reply = input('Do you want display each img? Y/N [Y]: ', 's');
if isempty(reply)|| strcmp(reply,'Y') || strcmp(reply,'y') 
    display = true;
else 
    display = false;
end

dispEr = [];
numEVals = minEVal:step:maxEVal;

for K= numEVals

    C = Evalue;
    % discard the diagonal values not required for compression
    C(K+1:end,:)=0;
    C(:,K+1:end)=0;

    % Construct an Image using the selected eign values
    A=Evector*C*invEv;
    % compute error
    errorImg = abs(A- inImageD);
    % display 
    if (display)
        figure;
        buffer = sprintf('Image output using %d eigen values', K);
        subplot(1,2,1);
        imshow(abs(A));
        title(buffer);
        subplot(1,2,2);
        imshow(errorImg);
        title('Error Image');
    end
    error = norm(errorImg,'fro');

    % store vals for display
    dispEr = [dispEr; error];
    
end

%dislay the error graph
figure; 
title('Error in compression');
plot(numEVals, dispEr);
grid on
xlabel('Number of Eign Values used(N)');
ylabel('Error between compress and original image (Frobenius norm)');
