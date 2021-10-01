set /P cmt=Enter commit msg:
git add -A
git commit -m "%cmt%"
git push origin main