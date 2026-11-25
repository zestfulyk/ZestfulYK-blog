# 项目规则：ZestfulYK 博客（Hexo 8 + Butterfly 5.5.2）

## 仓库与分支

- 源码分支 `main`（唯一工作分支）：`source/`、`_config*.yml`、`package.json`、`themes/`。
- 发布分支 `gh-pages`：只由 `hexo deploy` 写入，禁止手动 commit，禁止合并回 `main`。
- 禁止在 `main` 上拉取/合并发布分支；禁止把 `public/`、`db.json`、`.deploy_git/` 入库。
- 发布分支之所以独立：`hexo deploy` 会用 `public/` 快照**强推覆盖**目标分支，与源码同分支会删掉源码。

## 环境事实（本机实测，务必按此执行）

- **没有全局 hexo**。统一用 `./node_modules/.bin/hexo <cmd>`；
  `which hexo` 命中的 `~/.nvmd/bin/hexo.exe` 是失效桩，会报"不是内部或外部命令"。
- **没有 SVG/图片渲染工具**：`convert` 是 Windows NTFS 卷工具（禁用），无 ImageMagick/rsvg/inkscape。
  改图只能在文本层校验（`polyline points` 与 `circle cx/cy` 逐点比对），最终视觉确认交给用户。
- 路径含中文；git 输出加 `-c core.quotepath=false`；仓库既有文件为 CRLF、新文件为 LF，均无 `.gitattributes`。
- 系统时钟在 2026 年，`hexo new` 生成的日期会"在未来"。
- 代码页 936：Windows 原生命令的中文输出在 bash 里会乱码，属正常现象。

## 目录职责

- `source/_posts/`：文章 + 同名资源目录（`post_asset_folder: true`，正文用相对名 `![](fig1.svg)`）。
- `source/{about,friends,categories,tags}/index.md`：页面源。
- `source/images/`：站点静态图（`_config.butterfly.yml` 里 `/images/...` 指这里）。
- `source/主席树.html`、`source/彳亍法词表.html`：`skip_render` 静态页，直接输出。
- `themes/butterfly/`：主题源码（`_config.yml` 有本地改动）；站点外观优先改根目录 `_config.butterfly.yml`。
- 不在仓库根目录放任何生成产物（`index.html`、`20xx/`、`archives/`、`search.xml` 等）。

## 命令边界

- 只允许 Hexo CLI：`hexo new`、`hexo server`、`hexo clean`、`hexo generate`、`hexo deploy`。
- `npm`、`pnpm`、`npx`：需先说明理由并取得用户授权。
- Git 写操作（`add`/`commit`/`push`/`merge`/`reset`/`checkout`）：需先取得用户授权。
- 发布流程：`hexo clean && hexo generate && hexo deploy`（推到 `gh-pages`）。
  站点根路径为 `/ZestfulYK-blog/`，发布后抽检 `/images/`、`/img/`、两个 `skip_render` 页。

## 交付报告

- 说明修改了哪些源文件、执行了哪些 Hexo 命令、验证结果如何。
- 未执行验证要说明原因；Git 提交不作为完成条件。
