close all
clear all
clc

IMGPATH = '../DSC01934.jpg';
inImage=imread(IMGPATH);
inImage=rgb2gray(inImage);
inImageD=im2double(inImage);

AtA=inImageD'*inImageD;
% decomposing the image into Eign values and Eigen Vectors
[Evector,Evalue] = eig(AtA);


%Sort Evector and Evalue
sortedEv=diag(sort(diag(Evalue),'descend')); 
[c, ind]=sort(diag(Evalue),'descend');
Evector=Evector(:,ind);
Evalue = sortedEv;


k = input('Enter No of Eign Values');

% discard the diagonal values not required for compression
Evalue(k+1:end,:)=0;
Evalue(:,k+1:end)=0;

% Construct an Image using the selected eign values

AtAnew=Evector*Evalue*Evector';
A = (AtAnew/inImageD)';

errorImg = inImageD-A;
% display and compute error
buffer = sprintf('Image_eign_3_%d.jpg', k);
imwrite(A,buffer);
buffer = sprintf('Image_3_er_%d.jpg', k);
imwrite(uint8(errorImg),buffer);

% err = sum ij((Dij - oldDij))
error=norm(errorImg,'fro');

buffer = sprintf('Error is = %d',error);
disp(buffer);