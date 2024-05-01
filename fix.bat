@echo off
SETLOCAL ENABLEEXTENSIONS

:: 设置旧的用户名和邮箱
SET OLD_NAME="TochusC"
SET OLD_EMAIL="tochusc@gmail.com"

:: 设置新的用户名和邮箱
SET NEW_NAME="TochusC"
SET NEW_EMAIL="205329624@qq.com"

:: 使用Git命令重写历史
git filter-branch --env-filter "

:: 如果GIT_COMMITTER_NAME和GIT_COMMITTER_EMAIL匹配旧值，则替换为新的值
if [ \"\$GIT_COMMITTER_NAME\" = \"%OLD_NAME%\" ] &&
   [ \"\$GIT_COMMITTER_EMAIL\" = \"%OLD_EMAIL%\" ];
then
  export GIT_COMMITTER_NAME=\"%NEW_NAME%\"
  export GIT_COMMITTER_EMAIL=\"%NEW_EMAIL%\"
fi

:: 如果GIT_AUTHOR_NAME和GIT_AUTHOR_EMAIL匹配旧值，则替换为新的值
if [ \"\$GIT_AUTHOR_NAME\" = \"%OLD_NAME%\" ] &&
   [ \"\$GIT_AUTHOR_EMAIL\" = \"%OLD_EMAIL%\" ];
then
  export GIT_AUTHOR_NAME=\"%NEW_NAME%\"
  export GIT_AUTHOR_EMAIL=\"%NEW_EMAIL%\"
fi
" HEAD

ENDLOCAL

git push --force --all
