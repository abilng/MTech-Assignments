function line=makeLine(matrix)
n = size(matrix,1);
line = [];
for i = 1:n
    line = [line matrix(i,:)];
end
end